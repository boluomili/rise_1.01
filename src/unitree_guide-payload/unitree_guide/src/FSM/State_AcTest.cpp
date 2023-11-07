/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#include "FSM/State_AcTest.h"
#include <iomanip>
#include<dynamic_reconfigure/server.h>
#include<unitree_guide/riseConfig.h>
#include <iostream>
#include <fstream>



State_AcTest::State_AcTest(CtrlComponents *ctrlComp)
             :FSMState(ctrlComp, FSMStateName::ACTEST, "acTest"), 
              _est(ctrlComp->estimator), _phase(ctrlComp->phase), 
              _contact(ctrlComp->contact), _robModel(ctrlComp->robotModel), 
              _balCtrl(ctrlComp->balCtrl),_pub(ctrlComp->pub){
    _gait = new GaitGenerator(ctrlComp);

    _gaitHeight = 0.08;

#ifdef ROBOT_TYPE_Go1
    _Kpp = Vec3(70, 70, 70).asDiagonal();
    _Kdp = Vec3(10, 10, 10).asDiagonal();
    _kpw = 780; 
    _Kdw = Vec3(70, 70, 70).asDiagonal();
    _KpSwing = Vec3(400, 400, 400).asDiagonal();
    _KdSwing = Vec3(10, 10, 10).asDiagonal();
    //***********8.29***************

    
    //***********8.29***************
#endif

#ifdef ROBOT_TYPE_A1
    _Kpp = Vec3(20, 20, 100).asDiagonal();
    _Kdp = Vec3(20, 20, 20).asDiagonal();
    _kpw = 400;
    _Kdw = Vec3(50, 50, 50).asDiagonal();
    _KpSwing = Vec3(400, 400, 400).asDiagonal();
    _KdSwing = Vec3(10, 10, 10).asDiagonal();
#endif
    //x,y,z轴转动--限制
    _vxLim = _robModel->getRobVelLimitX();
    _vyLim = _robModel->getRobVelLimitY();
    _wyawLim = _robModel->getRobVelLimitYaw();

    //仿真参数  负载估计
    _KD = Vec3(0,0,0.01).asDiagonal();
    _Gammam = 2;
    _lamda = 25;
    //力矩估计
    _KDTu = Vec3(1.5,1.5,0.5).asDiagonal();
    _lamdaTu = Vec3(25, 25, 5).asDiagonal();
    _GammaTu = Vec3(1.5, 1.5, 0.7).asDiagonal();

    //变高度
    // _KD = Vec3(0,0,0.001).asDiagonal();
    // _Gammam = 15;
    // _lamda = 20;

    //实机参数
    // _KD = Vec3(0,0,0.02).asDiagonal();
    // _Gammam = 15;
    // _lamda = 5;

    // _KDTu = Vec3(1.5,1.5,0.5).asDiagonal();
    // _lamdaTu = Vec3(1, 1, 0.5).asDiagonal();
    // _GammaTu = Vec3(1.5, 1.5, 0.7).asDiagonal();



}

State_AcTest::~State_AcTest(){
    delete _gait;
}
//*************************
// dynamic_reconfigure::Server<dynamic_reconfigure_test::riseConfig> *dsrv_;
// dsrv_ = new dynamic_reconfigure::Server<dynamic_reconfigure_test::riseConfig>(ros::NodeHandle("~/" + name));
// dynamic_reconfigure::Server<dynamic_reconfigure_test::riseConfig>::CallbackType cb = boost::bind(&dynamic_reconfigure_test::reconfigureCB, this, _1, _2);

// void GlobalPlanner::reconfigureCB(global_planner::GlobalPlannerConfig& config, uint32_t level) {
//     K_s=config.K_s;
//     _beita=config.beita;
//     alphe1=config.alphe1;
//     alphe2=config.alphe2;
    
// }
//**********************************

void State_AcTest::enter(){
    FILE *input1;
    input1 = fopen("AC_DOB.txt","w");   //write写入
    //fprintf(input1,"%s %s %s %s %s %s %s %s\n","负载质量","质量更新律","机身高度","期望机身高度","机身速度x","期望速度", "机身高度误差", "速度误差x");
    fclose(input1);
    _pcd = _est->getPosition();
    _pcd(2) = -_robModel->getFeetPosIdeal()(2, 0);
    _vCmdBody.setZero();
    _yawCmd = _lowState->getYaw();
    _Rd = rotz(_yawCmd);
    _wCmdGlobal.setZero();

    _ctrlComp->ioInter->zeroCmdPanel();
    _gait->restart();

    _d_mb = 0;          //这是什么
    _mb = 0;


    //***********8.29***************
    // K_s=100;
    // _beita=115;
    // alphe1=40;
    // alphe2=30;
    K_s=2;
    _beita=0.5;
    alphe1=20;
    alphe2=5;
    pos_integral.setZero();
    pos_integral_d.setZero();

    //     extern dynamic_reconfigure::Server<dynamic_reconfigure_test::riseConfig> server;
    // //定义回调函数
    // extern dynamic_reconfigure::Server<dynamic_reconfigure_test::riseConfig>::CallbackType f;
    // f = boost::bind(&Callback,_1);
    // server.setCallback(f);


    //***********8.29***************


    _Loading.setZero();     //这是什么

    _Tu.setZero();
    _E.setIdentity();
    _U.setZero();
    _kexi.setZero();


//***********8.29***************
    miu_t.setZero();
    integral.setZero();
    _error2_0.setZero();
    _error2.setZero();

//***********8.29***************


    _num = 0;
    _firstRun = true;


    

}

void State_AcTest::exit(){
    _ctrlComp->ioInter->zeroCmdPanel();
    _ctrlComp->setAllSwing();
}
    //按键检测，改变状态
FSMStateName State_AcTest::checkChange(){
    if(_lowState->userCmd == UserCommand::L2_B){
        return FSMStateName::PASSIVE;
    }
    else if(_lowState->userCmd == UserCommand::L2_A){
        return FSMStateName::FIXEDSTAND;
    }
    else if(_lowState->userCmd == UserCommand::START){
        return FSMStateName::TROTTING;
    }
    else{
        return FSMStateName::ACTEST;
    }
}

void State_AcTest::run(){
    _posBody = _est->getPosition();
    _velBody = _est->getVelocity();
    _posFeet2BGlobal = _est->getPosFeet2BGlobal();
    _posFeetGlobal = _est->getFeetPos();
    _velFeetGlobal = _est->getFeetVel();
    _B2G_RotMat = _lowState->getRotMat();
    _G2B_RotMat = _B2G_RotMat.transpose();
    _yaw = _lowState->getYaw();
    _dYaw = _lowState->getDYaw();

        //将回调函数和服务端绑定，当客户端请求修改参数时，服务器跳转到回调函数进行处理



    // std::cout<< "机身姿态矩阵 = " << _B2G_RotMat <<std::endl; 
    // std::cout<< "世界转机身旋转矩阵 = " << _G2B_RotMat <<std::endl; 
    // std::cout<< "期望姿态矩阵 = " << _Rd <<std::endl; 

    _userValue = _lowState->userValue;

    getUserCmd();
    calcCmd();
        //设置x，y的速度，以及z轴转速。
    _gait->setGait(_vCmdGlobal.segment(0,2), _wCmdGlobal(2), _gaitHeight);
    // _gait->run(_posFeetGlobalGoal, _velFeetGlobalGoal);
    //由足端位置，足端速度，角度，计算出相应轨迹。
    _gait->run(_posFeetGlobalGoal, _velFeetGlobalGoal);
    // _gait->run(_posFeetGlobalGoal, _velFeetGlobalGoal, _Angle);

    if(_firstRun)
    {
        _Pi = _est->getFeetPos();//第一次运行
        _firstRun = false;
        _lastxposition = _Pi.col(2)[0];//Pi当前足端位置，第3列1行
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

    _dAngle = (_YM.transpose()*_YM).inverse()*_YM.transpose()*_ZM;
    _Angle(0) = atan(_dAngle(0));
    _Angle(1) = atan(_dAngle(1));
    _Angle(2) = atan(_dAngle(2));
    // _Angle(1) = saturation(_Angle(1), Vec2(0.2, -0.2));
    _lastxposition = _Pi.col(2)[0];

    //std::cout<< "斜坡倾角 = " << _Angle.transpose() <<std::endl; 

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
            //检测站立是否
bool State_AcTest::checkStepOrNot(){
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
        //设置高层命令，机身速度，角速度
void State_AcTest::setHighCmd(double vx, double vy, double wz){
    _vCmdBody(0) = vx;
    _vCmdBody(1) = vy;
    _vCmdBody(2) = 0; 
    _dYawCmd = wz;
}

void State_AcTest::getUserCmd(){
    /* Movement */
    _vCmdBody(0) =  invNormalize(_userValue.ly, _vxLim(0), _vxLim(1));
    _vCmdBody(1) = -invNormalize(_userValue.lx, _vyLim(0), _vyLim(1));
    _vCmdBody(2) = 0;
    // if(count<1000){
    //     _vCmdBody(0) =  count*0.001;
    // }else{
    //     _vCmdBody(0) =  1.0;
    // }  
    _vCmdBody(1) = -invNormalize(_userValue.lx, _vyLim(0), _vyLim(1));
    _vCmdBody(2) = 0;

    /* Turning */
    _dYawCmd = -invNormalize(_userValue.rx, _wyawLim(0), _wyawLim(1));
    _dYawCmd = 0.9*_dYawCmdPast + (1-0.9) * _dYawCmd;
    _dYawCmdPast = _dYawCmd;

    //角速度修改，角速度渐大至3
    if(count<1500){
        _dYawCmd =  count*0.002;
    }else{
        _dYawCmd =  3.0;
    }
    //这一行使用滑动平均的方法来平滑转向命令
    _dYawCmd = 0.80*_dYawCmdPast + (1-0.80) * _dYawCmd;
    _dYawCmdPast = _dYawCmd;
}

void State_AcTest::calcCmd(){
    /* Movement */
    _vCmdGlobal = _B2G_RotMat * _vCmdBody;

    _vCmdGlobal(0) = saturation(_vCmdGlobal(0), Vec2(_velBody(0)-0.2, _velBody(0)+0.2));
    _vCmdGlobal(1) = saturation(_vCmdGlobal(1), Vec2(_velBody(1)-0.2, _velBody(1)+0.2));

    _pcd(0) = saturation(_pcd(0) + _vCmdGlobal(0) * _ctrlComp->dt, Vec2(_posBody(0) - 0.05, _posBody(0) + 0.05));
    _pcd(1) = saturation(_pcd(1) + _vCmdGlobal(1) * _ctrlComp->dt, Vec2(_posBody(1) - 0.05, _posBody(1) + 0.05));

    _vCmdGlobal(2) = 0;

    /* Turning */
    _yawCmd = _yawCmd + _dYawCmd * _ctrlComp->dt;

    _Rd = rotz(_yawCmd);

    // if(_Pi.col(0)[0]-_lastxposition>=0&&_Pi.col(0)[0]>0)
    // {
    //     _Rd = rotz(_yawCmd)*roty(-_Angle(1));
    // }else if(_Pi.col(0)[0]-_lastxposition<0&&_Pi.col(0)[0]>0)
    // {
    //     _Rd = rotz(_yawCmd)*roty(_Angle(1));
    // }else if(_Pi.col(0)[0]-_lastxposition>=0&&_Pi.col(0)[0]<0)
    // {
    //     _Rd = rotz(_yawCmd)*roty(-_Angle(1));
    // }else if(_Pi.col(0)[0]-_lastxposition<0&&_Pi.col(0)[0]<0)
    // {
    //     _Rd = rotz(_yawCmd)*roty(_Angle(1));
    // }

    // std::cout<< "足端X坐标 = " << _Pi.col(0)[0] <<std::endl; 
    // std::cout<< "上一时刻足端X坐标 = " << _lastxposition <<std::endl; 
    _wCmdGlobal(2) = _dYawCmd;
}

int State_AcTest::sgn(double val){
    if(-0.05<val&&val<0.05)
{
    val=0;
}
if(val>0.05)
{
    val=1;
}

if(val<-0.05)
{
    val=-1;
}

//std::cout<<val<<std::endl;
return val;
}

void State_AcTest::calcTau(){
    //_pcd(2) = 0.29;
    // _pcd(2) = 0.22 + 0.1*sin(0.1*1.57 * _num * _ctrlComp->dt);
    // _num++;
    _posError = _pcd - _posBody;
    _velError = _vCmdGlobal - _velBody;
    
    
    //ddp就是期望加速度。
    _ddPcd = _Kpp * _posError + _Kdp * _velError;
    //目标角加速度
    _dWbd  = _kpw*rotMatToExp(_Rd*_G2B_RotMat) + _Kdw * (_wCmdGlobal - _lowState->getGyroGlobal());

    _ddPcd(0) = saturation(_ddPcd(0), Vec2(-3, 3));     //satur限制范围
    _ddPcd(1) = saturation(_ddPcd(1), Vec2(-3, 3));
    _ddPcd(2) = saturation(_ddPcd(2), Vec2(-5, 5));

    _dWbd(0) = saturation(_dWbd(0), Vec2(-40, 40));
    _dWbd(1) = saturation(_dWbd(1), Vec2(-40, 40));
    _dWbd(2) = saturation(_dWbd(2), Vec2(-10, 10));

    //平动
    _S_Compound = -_velError - _lamda * _posError;      //复合误差
    _Ym = _ddPcd + _lamda * _velError + Vec3(0,0,9.81); //Y_p,辅助变量
    _d_mb = -_Gammam * _Ym.transpose() * _S_Compound;   //质量更新律
    _mb = _mb + _d_mb * _ctrlComp->dt;                  //估计质量
    //***********8.29***************
    //***********8.29***************

           
    _Loading = _Ym * _mb - _KD *_S_Compound;            //估计-力
        //box可删，
    double _box_mass;
    _box_mass = _Loading(2)/(_ddPcd(2) + 9.81) ;

    // std::cout<<"_box_mass= "<<_box_mass<<std::endl;   
    // std::cout<<"_pcd= "<<_pcd.transpose()<<std::endl;
    // std::cout<<"_posBody= "<<_posBody.transpose()<<std::endl;
    //std::cout<<"_vCmdGlobal = "<<_vCmdGlobal.transpose()<<std::endl;
    //std::cout<<"_velBody = "<<_velBody.transpose()<<std::endl;
    // std::cout<<"_velError= "<<_velError.transpose()<<std::endl;
    // std::cout<<"_S_Compound = "<< _S_Compound.transpose() <<std::endl;
    // std::cout<<"_Ym = "<< _Ym.transpose() <<std::endl;
    // std::cout<<"_d_mb = "<< _d_mb <<std::endl;
    //std::cout<<"_mb = "<< _mb <<std::endl;
    // std::cout<<"_Loading = "<< _Loading.transpose() <<std::endl;

    //转动
    Vec3 _rotError = rotMatToExp(_Rd*_G2B_RotMat);
    Vec3 _wError = -_lowState->getGyroGlobal() + _wCmdGlobal;
    Mat3 _Ibody = Vec3(0.0792, 0.2085, 0.2265).asDiagonal();    
        //asDiagonal对角矩阵
        

    _S_CompoundTu = _wError + _lamdaTu * _rotError;     //复合误差
    _Tu = _GammaTu*_Ibody*_lowState->getGyroGlobal() + _kexi;//_Tu = d
    _dkexi = -_GammaTu*(_U + _Tu);
    _kexi = _kexi + _dkexi* _ctrlComp->dt;
    //_U = -(_KDTu*_lamdaTu + _E)*_rotError-(_KDTu + _lamdaTu)*_wError-_Tu;
   


        //***********8.29***************  
        _error2=_wError+alphe1*_rotError;
        static Vec3 _error2_0=_error2;
    for ( int i(0); i<3; ++i)
    {
        templesgn(i)=sgn(_error2(i));
    }

    integral=integral+(K_s+1)*alphe2*_error2*_ctrlComp->dt+_beita*templesgn*_ctrlComp->dt;
    miu_t=(K_s+1)*_error2-(K_s+1)*_error2_0 + integral;

    _U = _Ibody*alphe1*_wError+_Ibody*alphe2*_error2+miu_t;
    //计算实际的位置
    pos_integral(0)=pos_integral(0)+_ctrlComp->dt*_velBody(0);
    pos_integral(1)=pos_integral(1)+_ctrlComp->dt*_velBody(1);
    pos_integral(2)=pos_integral(2)+_ctrlComp->dt*_velBody(2);

    //计算期望的位置
    pos_integral_d(0)=pos_integral_d(0)+_ctrlComp->dt*_vCmdBody(0);
    pos_integral_d(1)=pos_integral_d(1)+_ctrlComp->dt*_vCmdBody(1);
    pos_integral_d(2)=pos_integral_d(2)+_ctrlComp->dt*_vCmdBody(2);

    //x方向上的误差
    double pos_error_0;
    pos_error_0=pos_integral_d(0)-pos_integral(0);

    count_1=0;
    if(count_1%100==0)
    {
    std::cout<<"_dWbd的值:= "<< _dWbd.transpose()<<std::endl;
    std::cout<<"_rotError的值:= "<< _rotError.transpose()<<std::endl;
    std::cout<<"_wError的值:= "<< _wError.transpose()<<std::endl;
    std::cout<<"_error2的值:= "<< _error2.transpose()<<std::endl;
    std::cout<<"_error2_0的值:= "<< _error2_0.transpose()<<std::endl;
    std::cout<<"integral的值:= "<< integral.transpose()<<std::endl;
    
    std::cout<<"估计质量为miu_t= "<< (miu_t/9.81).transpose()<<std::endl;
    std::cout<<"临时sgn的值= "<<templesgn.transpose()<<std::endl;
    std::cout<<"x方向位置误差的值= "<<pos_error_0<<std::endl;

    // std::cout<<"K_s,beita,alphe1,alphe2的值: "<<K_s<<"**"<<_beita<<"**"<<alphe1<<"**"<<alphe2<<"**"<<std::endl;

    // std::cout<<"K_s= "<<K_s<<std::endl;
    // std::cout<<"_beita= "<<_beita<<std::endl;
    // std::cout<<"alphe1 = "<<alphe1<<std::endl;
    // std::cout<<"alphe2 = "<<alphe2<<std::endl;
    }
    count_1++;
    //***********8.29***************
    
     
    
    // miu_t=(K_s+1)*_error2-(K_s+1)*_error2_0+integral;
    
    //std::cout<<"_dYawCmd = "<<_dYawCmd<<std::endl;
    //std::cout<<"_yaw = "<< _yaw <<std::endl;
    // std::cout<<"_S_CompoundTu = "<< _S_CompoundTu.transpose() <<std::endl;
    // std::cout<<"_Tu = "<< _Tu.transpose() <<std::endl;
    // std::cout<<"_U = "<< _U.transpose() <<std::endl;

    _forceFeetGlobal = - _balCtrl->calF(_ddPcd, _dWbd, _B2G_RotMat, _posFeet2BGlobal, *_contact, _Loading(2), _U);
    
    //_forceFeetGlobal = - _balCtrl->calF(_ddPcd, _dWbd, _B2G_RotMat, _posFeet2BGlobal, *_contact);
   
    // _forceFeetGlobal = - _balCtrl->calF(_ddPcd, _dWbd, _B2G_RotMat, _posFeet2BGlobal, *_contact, 0, Vec3(0,0,0));
    //如果是非接触状态，则计算每条腿的足端力
    outputmass=miu_t(2)/9.81;
    for(int i(0); i<4; ++i){
        if((*_contact)(i) == 0){
            //_forceFeetGlobal.col(i) =_Ibody*_ddPcd+_Ibody*alphe1*_velError+_Ibody*alphe2*_error2+
            _forceFeetGlobal.col(i) = _KpSwing*(_posFeetGlobalGoal.col(i) - _posFeetGlobal.col(i)) + _KdSwing*(_velFeetGlobalGoal.col(i)-_velFeetGlobal.col(i));
        }
    }
        //求四条腿z轴方向的力，然后加在一起构成z方向的合力
    double mm = 0;
    Vec12 q;
    q = vec34ToVec12(_forceFeetGlobal);
    for (int i = 0; i < 12; i++)
    {   
        if((i+1)%3==0)
        {
            mm += -q[i];
        }
    }
        //世界系转身体系，地面力转系
    _forceFeetBody = _G2B_RotMat * _forceFeetGlobal;//足端力世界系转身体系
    _q = vec34ToVec12(_lowState->getQ());       //获取每个关节的转动角度
    _tau = _robModel->getTau(_q, _forceFeetBody);   //由关节角度和机身足端力求力矩

    if (count%5 == 0)
    {
        _pub->pub_data_mp(outputmass);
        _pub->pub_data_movement(_posBody, _pcd, _velBody, _vCmdGlobal, _lowState->getAccGlobal(), _ddPcd, mm, _d_mb, _posError, _velError,pos_error_0);
        _pub->pub_data_turning(rotMatToRPY(_B2G_RotMat),rotMatToRPY(_Rd),_lowState->getGyroGlobal(),_wCmdGlobal,_rotError,_wError,_Tu,_dkexi,_U);
        _pub->pub_data_rise(_posError,_velError,_error2,_error2_0,integral,miu_t,templesgn,miu_t/9.81);

        FILE *input1;
        input1 = fopen("AC_DOB.txt","a");
        fprintf(input1,"%f %f %f %f %f %f %f %f %f\n",miu_t(2)/9.81,_posBody(2),_pcd(2),_velBody(0),_vCmdGlobal(0), _velBody(1),_vCmdGlobal(1),_dYawCmd,_lowState->getGyroGlobal()(2));
        fclose(input1);
      
    //     _pub->sub_data_rise(K_s,_beita,alphe1,alphe2);
    //     using namespace std;
    //     ofstream dataFile;
    // dataFile.open("dataFile.txt",ofstream::app);
    // // 朝TXT文档中写入数据
    // dataFile << "_posError:" << _posError(2) << "\t_velError:" << _velError(2)<< "\tmass:" << miu_t(2)/9.81<<"\t_posBody:" << _posBody(2)<<"\t_velBody:" << _velBody(2)<< "\n";
    // // 关闭文档
    // dataFile.close();
        double mass_d=6.0;
            FILE *input10;
        input10 = fopen("dataFile10.txt","a");
        fprintf(input10,"%f %f %f %f %f %f %f %f\n",mass_d,miu_t(2)/9.81,_pcd(2),_posBody(2),_vCmdGlobal(0),_velBody(0),_posError(2),_velError(0));
        fclose(input10);

    }
 
    count++ ; 
    

    // for (int i = 0; i < 4; i++)
    // {
    //     std::cout<<"leg["<<i<<"]= "<< _tau[i*3+0] <<" "<<_tau[i*3+1] <<" "<< _tau[i*3+2] <<std::endl;
    // }

}

void State_AcTest::calcQQd(){

    Vec34 _posFeet2B;
    _posFeet2B = _robModel->getFeet2BPositions(*_lowState,FrameType::BODY);
    
    for(int i(0); i<4; ++i){
        _posFeet2BGoal.col(i) = _G2B_RotMat * (_posFeetGlobalGoal.col(i) - _posBody);
        _velFeet2BGoal.col(i) = _G2B_RotMat * (_velFeetGlobalGoal.col(i) - _velBody); 
        // _velFeet2BGoal.col(i) = _G2B_RotMat * (_velFeetGlobalGoal.col(i) - _velBody - _B2G_RotMat * (skew(_lowState->getGyro()) * _posFeet2B.col(i)) );  //  c.f formula (6.12) 
    }
            //各关节目标角度，各关节目标角速度。
    _qGoal = vec12ToVec34(_robModel->getQ(_posFeet2BGoal, FrameType::BODY));
    _qdGoal = vec12ToVec34(_robModel->getQd(_posFeet2B, _velFeet2BGoal, FrameType::BODY));
}



// gen.add("K_s", double_t, 0, "K_s_param", 0.0,  0, 500)
// gen.add("beita", double_t, 0, "beita_param", 0.0,  0, 500)
// gen.add("alphe1", double_t, 0, "alphe1_param", 0.0,  0, 500)
// gen.add("alphe2", double_t, 0, "alphe2_param", 0.0,  0, 500)
