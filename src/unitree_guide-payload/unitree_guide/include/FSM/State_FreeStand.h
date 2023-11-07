/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#ifndef FREESTAND_H
#define FREESTAND_H

#include "FSM/FSMState.h"
//机器人原地位姿控制
class State_FreeStand : public FSMState{
public:
    State_FreeStand(CtrlComponents *ctrlComp);
    ~State_FreeStand(){}
    void enter();
    void run();
    void exit();
    FSMStateName checkChange();
private:
    Vec3 _initVecOX;//机身坐标系{b}下X点（世界坐标系的原点）的初始坐标
    Vec34 _initVecXP;//世界坐标系{s}下各个落足点的初始坐标（按列排）
    float _rowMax, _rowMin;
    float _pitchMax, _pitchMin;
    float _yawMax, _yawMin;
    float _heightMax, _heightMin;

    Vec34 _calcOP(float row, float pitch, float yaw, float height);//计算机身目标位姿Tsb以及他的逆矩阵，最终利用（6.4）计算机身坐标系{b}下的各个足端的目标位置
    void _calcCmd(Vec34 vecOP);//根据目标落足点计算出各个关节的目标角度
};

#endif  // FREESTAND_H