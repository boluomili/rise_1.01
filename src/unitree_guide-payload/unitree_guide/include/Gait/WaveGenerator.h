/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#ifndef WAVEGENERATOR_H
#define WAVEGENERATOR_H

#include "common/mathTypes.h"
#include "common/timeMarker.h"
#include "common/enumClass.h"
#include <unistd.h>

#ifdef COMPILE_DEBUG
#include "common/PyPlot.h"
#endif  // COMPILE_DEBUG

/*generate linear wave, [0, 1] 根据时间生成四条腿的步态和相位*/
class WaveGenerator{
public:
    WaveGenerator(double period, double stancePhaseRatio, Vec4 bias);
    ~WaveGenerator();
    //计算四个足端的相位phaseResult、接触状态contactResult
    void calcContactPhase(Vec4 &phaseResult, VecInt4 &contactResult, WaveStatus status);
    //获取触地时长Tstance
    float getTstance();
    //获取腾空时长Tswing
    float getTswing();
    //获取步态周期T
    float getT();
private:
    //计算相位phase和接触状态contact
    void calcWave(Vec4 &phase, VecInt4 &contact, WaveStatus status);
    //步态周期P
    double _period;
    //触地系数
    double _stRatio;
    //四条腿偏移时间b与步态周期P的比值
    Vec4 _bias;

    Vec4 _normalT;                   // [0, 1)
    Vec4 _phase, _phasePast;
    VecInt4 _contact, _contactPast;
    VecInt4 _switchStatus;          // 1: switching, 0: do not switch
    WaveStatus _statusPast;

    double _passT;                   // unit: second
    long long _startT;    // unit: us
#ifdef COMPILE_DEBUG
    PyPlot _testPlot;
#endif  // COMPILE_DEBUG

};

#endif  // WAVEGENERATOR_H