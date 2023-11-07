/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#ifndef FEETENDCAL_H
#define FEETENDCAL_H

#include "control/CtrlComponents.h"
#include "message/LowlevelState.h"
//计算当前机器人状态下目标落脚点的位置坐标类 FeetEndCal
class FeetEndCal{
public:
    FeetEndCal(CtrlComponents *ctrlComp);
    ~FeetEndCal();
    //腿的序号、期望的机身平移速度、期望的机身旋转角速度、当前腿的相位
    Vec3 calFootPos(int legID, Vec2 vxyGoalGlobal, float dYawGoal, float phase);
    Vec3 calFootPos(int legID, Vec2 vxyGoalGlobal, float dYawGoal, float phase, double _gaitHeight, double theta);
private:
    LowlevelState *_lowState;
    Estimator *_est;
    QuadrupedRobot *_robModel;

    Vec3 _nextStep, _footPos;
    Vec3 _bodyVelGlobal;        // linear velocity
    Vec3 _bodyAccGlobal;        // linear accelerator
    Vec3 _bodyWGlobal;          // angular velocity

    Vec4 _feetRadius, _feetInitAngle;
    float _yaw, _dYaw, _nextYaw;

    float _Tstance, _Tswing;
    float _kx, _ky, _kyaw;
};

#endif  // FEETENDCAL_H