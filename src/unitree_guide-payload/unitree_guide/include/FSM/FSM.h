/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#ifndef FSM_H
#define FSM_H

// FSM States
#include "FSM/FSMState.h"
#include "FSM/State_FixedStand.h"
#include "FSM/State_Passive.h"
#include "FSM/State_FreeStand.h"
#include "FSM/State_Trotting.h"
#include "FSM/State_BalanceTest.h"
#include "FSM/State_SwingTest.h"
#include "FSM/State_StepTest.h"
#include "FSM/State_AcTest.h"
#include "common/enumClass.h"
#include "control/CtrlComponents.h"
#ifdef COMPILE_WITH_MOVE_BASE
    #include "FSM/State_move_base.h"
#endif  // COMPILE_WITH_MOVE_BASE

struct FSMStateList{
    FSMState *invalid;
    State_Passive *passive;
    State_FixedStand *fixedStand;
    State_FreeStand *freeStand;
    State_Trotting *trotting;
    State_BalanceTest *balanceTest;
    State_SwingTest *swingTest;
    State_StepTest *stepTest;
    State_AcTest *acTest;
#ifdef COMPILE_WITH_MOVE_BASE
    State_move_base *moveBase;
#endif  // COMPILE_WITH_MOVE_BASE

    void deletePtr(){
        delete invalid;
        delete passive;
        delete fixedStand;
        delete freeStand;
        delete trotting;
        delete balanceTest;
        delete swingTest;
        delete stepTest;
        delete acTest;
#ifdef COMPILE_WITH_MOVE_BASE
        delete moveBase;
#endif  // COMPILE_WITH_MOVE_BASE
    }
};

class FSM{
public:
    FSM(CtrlComponents *ctrlComp);
    ~FSM();
    void initialize();
    void run();
private:
    FSMState* getNextState(FSMStateName stateName);//根据状态的名字获取对应的状态指针
    bool checkSafty();//检查机器人是否安全（与z轴的夹角小于60度）
    CtrlComponents *_ctrlComp;
    FSMState *_currentState;
    FSMState *_nextState;
    FSMStateName _nextStateName;
    FSMStateList _stateList;//有限状态机的状态列表，（包含各种状态类的指针）
    FSMMode _mode;//有限状态机的模式，正常或者修改
    long long _startTime;//程序开始的时间
    int count;
};


#endif  // FSM_H