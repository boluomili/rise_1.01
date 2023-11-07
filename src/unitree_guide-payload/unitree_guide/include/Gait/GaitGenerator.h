/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#ifndef GAITGENERATOR_H
#define GAITGENERATOR_H

#include "Gait/WaveGenerator.h"
#include "Gait/FeetEndCal.h"

#ifdef COMPILE_DEBUG
#include <common/PyPlot.h>
#endif  // COMPILE_DEBUG

/*cycloid gait  摆线步态（计算摆线轨迹）*/
class GaitGenerator{
public:
    GaitGenerator(CtrlComponents *ctrlComp);
    ~GaitGenerator();
    //设置机身平移速度、机身偏航角速度、抬腿高度
    void setGait(Vec2 vxyGoalGlobal, float dYawGoal, float gaitHeight);
    //控制器每轮运行中，都会调用Run函数，能持续计算更新每个足端的目标落足点 参数：目标足端位置、足端速度
    void run(Vec34 &feetPos, Vec34 &feetVel);
    void run(Vec34 &feetPos, Vec34 &feetVel, Vec3 theta);
    //获取对应足端在当前时刻的目标位置
    Vec3 getFootPos(int i);
    //获取对应足端在当前时刻的目标速度
    Vec3 getFootVel(int i);
    void restart();
private:
    //获取摆线轨迹在X、Y方向的位置坐标
    float cycloidXYPosition(float startXY, float endXY, float phase);
    //获取摆线轨迹在X、Y方向的速度分量
    float cycloidXYVelocity(float startXY, float endXY, float phase);
    //获取摆线轨迹在Z方向上的位置坐标
    float cycloidZPosition(float startZ, float height, float phase);
    //获取摆线轨迹在Z方向的速度分量
    float cycloidZVelocity(float height, float phase);

    float CompositecycloidZPosition(float startZ, float height, float phase);

    float CompositecycloidZVelocity(float height, float phase);

    float getxPosition(float startXY, float endXY, float phase);
    float getxVelocity(float startXY, float endXY, float phase);

    WaveGenerator *_waveG;
    Estimator *_est;
    FeetEndCal *_feetCal;
    QuadrupedRobot *_robModel;
    LowlevelState *_state;
    float _gaitHeight;
    Vec2 _vxyGoal;
    float _dYawGoal;
    Vec4 *_phase, _phasePast;
    VecInt4 *_contact;
    Vec34 _startP, _endP, _idealP, _pastP;
    bool _firstRun;

#ifdef COMPILE_DEBUG
    PyPlot _testGaitPlot;
#endif  // COMPILE_DEBUG

};

#endif  // GAITGENERATOR_H