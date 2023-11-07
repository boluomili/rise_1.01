/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#ifndef CTRLCOMPONENTS_H
#define CTRLCOMPONENTS_H

#include "message/LowlevelCmd.h"
#include "message/LowlevelState.h"
#include "interface/IOInterface.h"
#include "interface/CmdPanel.h"
#include "common/unitreeRobot.h"
#include "Gait/WaveGenerator.h"
#include "control/Estimator.h"
#include "control/BalanceCtrl.h"
#include <string>
#include <iostream>
#include "control/pub.h"
#include "control/CalcSlopeAngle.h"

#ifdef COMPILE_DEBUG
#include "common/PyPlot.h"
#endif  // COMPILE_DEBUG

struct CtrlComponents{
public:
    CtrlComponents(IOInterface *ioInter):ioInter(ioInter){
        lowCmd = new LowlevelCmd();
        lowState = new LowlevelState();
        contact = new VecInt4;
        phase = new Vec4;
        *contact = VecInt4(0, 0, 0, 0);
        *phase = Vec4(0.5, 0.5, 0.5, 0.5);
    }
    ~CtrlComponents(){
        delete lowCmd;
        delete lowState;
        delete ioInter;
        delete robotModel;
        delete waveGen;
        delete estimator;
        delete balCtrl;
        delete pub;
        delete calcslopeangle;
#ifdef COMPILE_DEBUG
        delete plot;
#endif  // COMPILE_DEBUG
    }
    LowlevelCmd *lowCmd;//机器人底层命令
    LowlevelState *lowState;//机器人底层状态
    IOInterface *ioInter;//输入输出接口
    QuadrupedRobot *robotModel;//机器人模型
    WaveGenerator *waveGen;//步态发生器
    Estimator *estimator;//状态估计器
    BalanceCtrl *balCtrl;//平衡控制器
    Pub *pub;//发布消息
    CalcSlopeAngle *calcslopeangle;//计算斜坡倾角
 

#ifdef COMPILE_DEBUG
    PyPlot *plot;
#endif  // COMPILE_DEBUG

    VecInt4 *contact;//接触状态
    Vec4 *phase;

    double dt;//运行频率
    bool *running;//运行标志位
    CtrlPlatform ctrlPlatform;//控制平台

    void sendRecv(){
        ioInter->sendRecv(lowCmd, lowState);
    }

    void runWaveGen(){
        waveGen->calcContactPhase(*phase, *contact, _waveStatus);
    }

    void setAllStance(){
        _waveStatus = WaveStatus::STANCE_ALL;
    }

    void setAllSwing(){
        _waveStatus = WaveStatus::SWING_ALL;
    }

    void setStartWave(){
        _waveStatus = WaveStatus::WAVE_ALL;
    }

    void geneObj(){
        estimator = new Estimator(robotModel, lowState, contact, phase, dt);
        balCtrl = new BalanceCtrl(robotModel);
        pub = new Pub();
        calcslopeangle = new CalcSlopeAngle();

#ifdef COMPILE_DEBUG
        plot = new PyPlot();
        balCtrl->setPyPlot(plot);
        estimator->setPyPlot(plot);
#endif  // COMPILE_DEBUG
    }

private:
    WaveStatus _waveStatus = WaveStatus::SWING_ALL;

};

#endif  // CTRLCOMPONENTS_H