/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#ifndef IOINTERFACE_H
#define IOINTERFACE_H

#include "message/LowlevelCmd.h"
#include "message/LowlevelState.h"
#include "interface/CmdPanel.h"
#include <string>
//实现仿真和实机的接口基类（抽象类），接口的实现需要继承此基类，并实现sendRecv函数
class IOInterface{
public:
IOInterface(){}
~IOInterface(){delete cmdPanel;}
virtual void sendRecv(const LowlevelCmd *cmd, LowlevelState *state) = 0;
void zeroCmdPanel(){cmdPanel->setZero();}
void setPassive(){cmdPanel->setPassive();}

protected:
CmdPanel *cmdPanel;//实例化一个指向控制面板类的指针
};

#endif  //IOINTERFACE_H