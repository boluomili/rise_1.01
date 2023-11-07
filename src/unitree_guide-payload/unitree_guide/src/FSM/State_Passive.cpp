/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#include "FSM/State_Passive.h"

State_Passive::State_Passive(CtrlComponents *ctrlComp)
             :FSMState(ctrlComp, FSMStateName::PASSIVE, "passive"){}

void State_Passive::enter(){//将电机设置为阻尼状态
    if(_ctrlComp->ctrlPlatform == CtrlPlatform::GAZEBO){
        for(int i=0; i<12; i++){
            _lowCmd->motorCmd[i].mode = 10;
            _lowCmd->motorCmd[i].q = 0;
            _lowCmd->motorCmd[i].dq = 0;
            _lowCmd->motorCmd[i].Kp = 0;
            _lowCmd->motorCmd[i].Kd = 8;
            _lowCmd->motorCmd[i].tau = 0;
        }
    }
    else if(_ctrlComp->ctrlPlatform == CtrlPlatform::REALROBOT){
        for(int i=0; i<12; i++){
            _lowCmd->motorCmd[i].mode = 10;
            _lowCmd->motorCmd[i].q = 0;
            _lowCmd->motorCmd[i].dq = 0;
            _lowCmd->motorCmd[i].Kp = 0;
            _lowCmd->motorCmd[i].Kd = 3;
            _lowCmd->motorCmd[i].tau = 0;
        }
    }

    _ctrlComp->setAllSwing();
}

void State_Passive::run(){
    
}

void State_Passive::exit(){

}

FSMStateName State_Passive::checkChange(){
    if(_lowState->userCmd == UserCommand::L2_A){//手柄L2+A键 或 键盘2键 切换至固定站立状态
        return FSMStateName::FIXEDSTAND;
    }
    else{
        return FSMStateName::PASSIVE;
    }
}