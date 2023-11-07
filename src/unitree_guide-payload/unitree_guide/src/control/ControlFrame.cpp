/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#include "control/ControlFrame.h"
// _FSMController 实际运行的 run 函数是FSM类的 run 函数
ControlFrame::ControlFrame(CtrlComponents *ctrlComp):_ctrlComp(ctrlComp){
    _FSMController = new FSM(_ctrlComp);
}

void ControlFrame::run(){
    _FSMController->run();
}