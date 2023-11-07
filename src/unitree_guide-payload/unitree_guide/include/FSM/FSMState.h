/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#ifndef FSMSTATE_H
#define FSMSTATE_H

#include <string>
#include <iostream>
#include <unistd.h>
#include "control/CtrlComponents.h"
#include "message/LowlevelCmd.h"
#include "message/LowlevelState.h"
#include "common/enumClass.h"
#include "common/mathTools.h"
#include "common/mathTypes.h"
#include "common/timeMarker.h"
#include "interface/CmdPanel.h"
//管理机器人各种状态的有限状态机类（所有的状态类都继承它）
class FSMState{
public:
    FSMState(CtrlComponents *ctrlComp, FSMStateName stateName, std::string stateNameString);
    //在所有的子类中都要定义 enter()、run()、exit()函数
    virtual void enter() = 0;
    virtual void run() = 0;
    virtual void exit() = 0;
    //在所有子类中通常要改写checkChange()，实现不同状态的切换
    virtual FSMStateName checkChange() {return FSMStateName::INVALID;}

    FSMStateName _stateName;//当前状态机的名字
    std::string _stateNameString;
protected:
    CtrlComponents *_ctrlComp;
    FSMStateName _nextStateName;

    LowlevelCmd *_lowCmd;
    LowlevelState *_lowState;
    UserValue _userValue;
};

#endif  // FSMSTATE_H