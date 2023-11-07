/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#include "FSM/FSM.h"
#include <iostream>

FSM::FSM(CtrlComponents *ctrlComp)
    :_ctrlComp(ctrlComp){

    _stateList.invalid = nullptr;
    _stateList.passive = new State_Passive(_ctrlComp);
    _stateList.fixedStand = new State_FixedStand(_ctrlComp);
    _stateList.freeStand = new State_FreeStand(_ctrlComp);
    _stateList.trotting = new State_Trotting(_ctrlComp);
    _stateList.balanceTest = new State_BalanceTest(_ctrlComp);
    _stateList.swingTest = new State_SwingTest(_ctrlComp);
    _stateList.stepTest = new State_StepTest(_ctrlComp);
    _stateList.acTest = new State_AcTest(_ctrlComp);
#ifdef COMPILE_WITH_MOVE_BASE
    _stateList.moveBase = new State_move_base(_ctrlComp);
#endif  // COMPILE_WITH_MOVE_BASE
    initialize();//初始化有限状态机
}

FSM::~FSM(){
    _stateList.deletePtr();
}

void FSM::initialize(){
    _currentState = _stateList.passive;//设置当前状态为阻尼状态
    _currentState -> enter();//进入当前状态
    _nextState = _currentState;//设置下一个机器人的状态（保持阻尼状态）
    _mode = FSMMode::NORMAL;//设置有限状态机模式
}

void FSM::run(){
    _startTime = getSystemTime();//1.获取当前系统时间，这个函数返回一个long long类型的时间戳值，单位是微秒。
    _ctrlComp->sendRecv();//2.发送和接收机器人的命令和状态
    _ctrlComp->runWaveGen();
    _ctrlComp->estimator->run();
    if(!checkSafty()){
        _ctrlComp->ioInter->setPassive();//若姿态检测不安全，将机器人状态设置为阻尼状态（机器人会趴下）
    }

    if(_mode == FSMMode::NORMAL){//若当前有限状态机模式为NORMAL，执行以下操作
        _currentState->run();//执行当前状态的run函数
        _nextStateName = _currentState->checkChange();//获取下次循环时需要运行的状态（未来状态）
        if(_nextStateName != _currentState->_stateName){//当未来状态不为当前状态时
            _mode = FSMMode::CHANGE;//有限状态机的模式设置为CHANGE（切换模式）
            _nextState = getNextState(_nextStateName);//获取未来状态的指针
            std::cout << "Switched from " << _currentState->_stateNameString
                      << " to " << _nextState->_stateNameString << std::endl;
        }
    }
    else if(_mode == FSMMode::CHANGE){//若当前有限状态机模式为CHANGE，执行以下操作
        _currentState->exit();//执行当前状态的exit函数
        _currentState = _nextState;//将当前状态改为未来状态
        _currentState->enter();//执行新（状态）的enter函数
        _mode = FSMMode::NORMAL;//有限状态机的模式设置为NORMAL（正常模式，重复运行当前状态）
        _currentState->run();//执行当前状态的run函数
    }

    absoluteWait(_startTime, (long long)(_ctrlComp->dt * 1000000));
}

FSMState* FSM::getNextState(FSMStateName stateName){//返回一个状态类
    switch (stateName)
    {
    case FSMStateName::INVALID:
        return _stateList.invalid;
        break;
    case FSMStateName::PASSIVE:
        return _stateList.passive;
        break;
    case FSMStateName::FIXEDSTAND:
        return _stateList.fixedStand;
        break;
    case FSMStateName::FREESTAND:
        return _stateList.freeStand;
        break;
    case FSMStateName::TROTTING:
        return _stateList.trotting;
        break;
    case FSMStateName::BALANCETEST:
        return _stateList.balanceTest;
        break;
    case FSMStateName::SWINGTEST:
        return _stateList.swingTest;
        break;
    case FSMStateName::STEPTEST:
        return _stateList.stepTest;
        break;
    case FSMStateName::ACTEST:
        return _stateList.acTest;
        break;
#ifdef COMPILE_WITH_MOVE_BASE
    case FSMStateName::MOVE_BASE:
        return _stateList.moveBase;
        break;
#endif  // COMPILE_WITH_MOVE_BASE
    default:
        return _stateList.invalid;
        break;
    }
}

bool FSM::checkSafty(){
    // The angle with z axis less than 60 degree
    if(_ctrlComp->lowState->getRotMat()(2,2) < 0.5 ){
        return false;
    }else{
        return true;
    }
}