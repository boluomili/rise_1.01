/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#include "FSM/State_Trotting.h"
#include <iomanip>

State_Trotting::State_Trotting(CtrlComponents *ctrlComp)
             :FSMState(ctrlComp, FSMStateName::TROTTING, "trotting"), 
              _est(ctrlComp->estimator), _phase(ctrlComp->phase), 
              _contact(ctrlComp->contact), _robModel(ctrlComp->robotModel), 
              _balCtrl(ctrlComp->balCtrl),_pub(ctrlComp->pub),
              _calcslopeangle(ctrlComp->calcslopeangle){
    _gait = new GaitGenerator(ctrlComp);

    _gaitHeight = 0.15;

#ifdef ROBOT_TYPE_Go1
    _Kpp = Vec3(70, 70, 70).asDiagonal();
    _Kdp = Vec3(10, 10, 10).asDiagonal();
    _kpw = 780; 
    _Kdw = Vec3(70, 70, 70).asDiagonal();
    _KpSwing = Vec3(400, 400, 400).asDiagonal();
    _KdSwing = Vec3(10, 10, 10).asDiagonal();
#endif

#ifdef ROBOT_TYPE_A1
    _Kpp = Vec3(20, 20, 100).asDiagonal();
    _Kdp = Vec3(20, 20, 20).asDiagonal();
    _kpw = 400;
    _Kdw = Vec3(50, 50, 50).asDiagonal();
    _KpSwing = Vec3(400, 400, 400).asDiagonal();
    _KdSwing = Vec3(10, 10, 10).asDiagonal();
#endif

    _vxLim = _robModel->getRobVelLimitX();
    _vyLim = _robModel->getRobVelLimitY();
    _wyawLim = _robModel->getRobVelLimitYaw();

}

State_Trotting::~State_Trotting(){
    delete _gait;
}

void State_Trotting::enter(){
    FILE *input1;
    input1 = fopen("Balance1.txt","w");
    // fprintf(input1,"%s %s %s %s %s %s\n","机身高度","期望机身高度","机身速度x","期望速度", "机身高度误差", "速度误差x");
    fclose(input1);
    _pcd = _est->getPosition();
    _pcd(2) = -_robModel->getFeetPosIdeal()(2, 0);
    _vCmdBody.setZero();
    _yawCmd = _lowState->getYaw();
    _Rd = rotz(_yawCmd);
    _wCmdGlobal.setZero();
    pos_error_integral.setZero();

    _ctrlComp->ioInter->zeroCmdPanel();
    _gait->restart();

    _firstRun = true;
}

void State_Trotting::exit(){
    _ctrlComp->ioInter->zeroCmdPanel();
    _ctrlComp->setAllSwing();
}

FSMStateName State_Trotting::checkChange(){
    if(_lowState->userCmd == UserCommand::L2_B){
        return FSMStateName::PASSIVE;
    }
    else if(_lowState->userCmd == UserCommand::L2_A){
        return FSMStateName::FIXEDSTAND;
    }
    else if(_lowState->userCmd == UserCommand::L1_B){
        return FSMStateName::ACTEST;
    }
    else{
        return FSMStateName::TROTTING;
    }
}

void State_Trotting::run(){
    _posBody = _est->getPosition();
    _velBody = _est->getVelocity();
    _posFeet2BGlobal = _est->getPosFeet2BGlobal();
    _posFeetGlobal = _est->getFeetPos();
    _velFeetGlobal = _est->getFeetVel();
    _B2G_RotMat = _lowState->getRotMat();
    _G2B_RotMat = _B2G_RotMat.transpose();
    _yaw = _lowState->getYaw();
    _dYaw = _lowState->getDYaw();

    //----------------



    _userValue = _lowState->userValue;

    getUserCmd();
    calcCmd();

    _gait->setGait(_vCmdGlobal.segment(0,2), _wCmdGlobal(2), _gaitHeight);
    _gait->run(_posFeetGlobalGoal, _velFeetGlobalGoal, _Angle);//计算期望足端位置，速度

    if(_firstRun)
    {
        _Pi = _est->getFeetPos();//第一次运行
        _firstRun = false;
    }

    for(int i(0); i<4; ++i)
    {
        if((*_contact)(i)==1 && 0.2<(*_phase)(i)<0.8)
        {
          _Pi.col(i) = _est->getFeetPos().col(i);  
        }
    }

    _YM.col(1)  = (_Pi.row(0)).transpose();
    _YM.col(2) = (_Pi.row(1)).transpose();
    _YM.col(0) = Vec4(1,1,1,1);

    _ZM = (_Pi.row(2)).transpose();

    _Angle = (_YM.transpose()*_YM).inverse()*_YM.transpose()*_ZM;
    // _Angle(1) = saturation(_Angle(1), Vec2(0.2, -0.2));

    std::cout<< "斜坡倾角 = " << _Angle.transpose() <<std::endl; 
    // _SlopeAngle = _calcslopeangle->calAngle(_Pi);
    // std::cout<< "斜坡倾角 = " << _SlopeAngle <<std::endl; 

    calcTau();
    calcQQd();

    if(checkStepOrNot()){
        _ctrlComp->setStartWave();
    }else{
        _ctrlComp->setAllStance();
    }

    _lowCmd->setTau(_tau);
    _lowCmd->setQ(vec34ToVec12(_qGoal));
    _lowCmd->setQd(vec34ToVec12(_qdGoal));

    for(int i(0); i<4; ++i){
        if((*_contact)(i) == 0){
            _lowCmd->setSwingGain(i);
        }else{
            _lowCmd->setStableGain(i);
        }
    }

}

bool State_Trotting::checkStepOrNot(){
    if( (fabs(_vCmdBody(0)) > 0.03) ||
        (fabs(_vCmdBody(1)) > 0.03) ||
        (fabs(_posError(0)) > 0.08) ||
        (fabs(_posError(1)) > 0.08) ||
        (fabs(_velError(0)) > 0.05) ||
        (fabs(_velError(1)) > 0.05) ||
        (fabs(_dYawCmd) > 0.20) ){
        return true;
    }else{
        return false;
    }
}

void State_Trotting::setHighCmd(double vx, double vy, double wz){
    _vCmdBody(0) = vx;
    _vCmdBody(1) = vy;
    _vCmdBody(2) = 0; 
    _dYawCmd = wz;
}

void State_Trotting::getUserCmd(){
    /* Movement */
    _vCmdBody(0) =  invNormalize(_userValue.ly, _vxLim(0), _vxLim(1));
    _vCmdBody(1) = -invNormalize(_userValue.lx, _vyLim(0), _vyLim(1));
    _vCmdBody(2) = 0;

        if(count<1000){
        _vCmdBody(0) =  count*0.001;
    }else{
        _vCmdBody(0) =  1.0;
    }  

    /* Turning */
    _dYawCmd = -invNormalize(_userValue.rx, _wyawLim(0), _wyawLim(1));
    _dYawCmd = 0.9*_dYawCmdPast + (1-0.9) * _dYawCmd;
    _dYawCmdPast = _dYawCmd;
}

void State_Trotting::calcCmd(){
    /* Movement */
    _vCmdGlobal = _B2G_RotMat * _vCmdBody;

    _vCmdGlobal(0) = saturation(_vCmdGlobal(0), Vec2(_velBody(0)-0.2, _velBody(0)+0.2));
    _vCmdGlobal(1) = saturation(_vCmdGlobal(1), Vec2(_velBody(1)-0.2, _velBody(1)+0.2));

    _pcd(0) = saturation(_pcd(0) + _vCmdGlobal(0) * _ctrlComp->dt, Vec2(_posBody(0) - 0.05, _posBody(0) + 0.05));
    _pcd(1) = saturation(_pcd(1) + _vCmdGlobal(1) * _ctrlComp->dt, Vec2(_posBody(1) - 0.05, _posBody(1) + 0.05));

    _vCmdGlobal(2) = 0;

    /* Turning */
    _yawCmd = _yawCmd + _dYawCmd * _ctrlComp->dt;
    if(_Pi.col(0)[2]>_Pi.col(2)[2])
    {
        _Rd = rotz(_yawCmd)*roty(-_Angle(1));
    }else
    {
        _Rd = rotz(_yawCmd)*roty(_Angle(1));
    }
    _wCmdGlobal(2) = _dYawCmd;
}

void State_Trotting::calcTau(){
    _posError = _pcd - _posBody;
    _velError = _vCmdGlobal - _velBody;
    
    pos_error_integral=pos_error_integral+_vCmdGlobal*_ctrlComp->dt-_velBody*_ctrlComp->dt;

    _ddPcd = _Kpp * _posError + _Kdp * _velError;
    _dWbd  = _kpw*rotMatToExp(_Rd*_G2B_RotMat) + _Kdw * (_wCmdGlobal - _lowState->getGyroGlobal());

    _ddPcd(0) = saturation(_ddPcd(0), Vec2(-3, 3));
    _ddPcd(1) = saturation(_ddPcd(1), Vec2(-3, 3));
    _ddPcd(2) = saturation(_ddPcd(2), Vec2(-5, 5));

    _dWbd(0) = saturation(_dWbd(0), Vec2(-40, 40));
    _dWbd(1) = saturation(_dWbd(1), Vec2(-40, 40));
    _dWbd(2) = saturation(_dWbd(2), Vec2(-10, 10));

    _forceFeetGlobal = - _balCtrl->calF(_ddPcd, _dWbd, _B2G_RotMat, _posFeet2BGlobal, *_contact);

    for(int i(0); i<4; ++i){
        if((*_contact)(i) == 0){
            _forceFeetGlobal.col(i) = _KpSwing*(_posFeetGlobalGoal.col(i) - _posFeetGlobal.col(i)) + _KdSwing*(_velFeetGlobalGoal.col(i)-_velFeetGlobal.col(i));
        }
    }

    double mm = 0;
    Vec12 q;
    q = vec34ToVec12(_forceFeetGlobal);
    for (int i = 0; i < 12; i++)
    {   
        // std::cout<<"Footforce["<<i<<"]="<<q[i]<<std::endl;
        if((i+1)%3==0)
        {
            mm += -q[i];
        }
    } 

    // std::cout<<"_pcd= "<<_pcd.transpose()<<std::endl;
    // std::cout<<"_posBody= "<<_posBody.transpose()<<std::endl;
    // std::cout<<"足端力 = "<<q.transpose()<<std::endl;
    // std::cout<<"Z方向力之和 = "<<mm<<std::endl;

    _forceFeetBody = _G2B_RotMat * _forceFeetGlobal;
    _q = vec34ToVec12(_lowState->getQ());
    _tau = _robModel->getTau(_q, _forceFeetBody);

    if (count%5 == 0)
    {
        _pub->pub_data_movement(_posBody, _pcd, _velBody, _vCmdGlobal, _lowState->getAccGlobal(), _ddPcd, mm, 0, _posError, _velError,pos_error_integral(0));
        
        FILE *input1;
        input1 = fopen("Balance1.txt","a");
        fprintf(input1,"%f %f %f %f %f %f\n",_posBody(2),_pcd(2),_velBody(0),_vCmdGlobal(0), _posError(2), _velError(0));
        fclose(input1);
    }

    count++ ; 
    
    // for (int i = 0; i < 4; i++)
    // {
    //     std::cout<<"leg["<<i<<"]= "<< _tau[i*3+0] <<" "<<_tau[i*3+1] <<" "<< _tau[i*3+2] <<std::endl;
    // }
}

void State_Trotting::calcQQd(){

    Vec34 _posFeet2B;
    _posFeet2B = _robModel->getFeet2BPositions(*_lowState,FrameType::BODY);
    
    for(int i(0); i<4; ++i){
        _posFeet2BGoal.col(i) = _G2B_RotMat * (_posFeetGlobalGoal.col(i) - _posBody);
        _velFeet2BGoal.col(i) = _G2B_RotMat * (_velFeetGlobalGoal.col(i) - _velBody); 
        // _velFeet2BGoal.col(i) = _G2B_RotMat * (_velFeetGlobalGoal.col(i) - _velBody - _B2G_RotMat * (skew(_lowState->getGyro()) * _posFeet2B.col(i)) );  //  c.f formula (6.12) 
    }
    
    _qGoal = vec12ToVec34(_robModel->getQ(_posFeet2BGoal, FrameType::BODY));
    _qdGoal = vec12ToVec34(_robModel->getQd(_posFeet2B, _velFeet2BGoal, FrameType::BODY));
}

