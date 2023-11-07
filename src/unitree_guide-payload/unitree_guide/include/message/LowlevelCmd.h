/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#ifndef LOWLEVELCMD_H
#define LOWLEVELCMD_H

#include "common/mathTypes.h"
#include "common/mathTools.h"
//存储电机底层命令的结构体 MotorCmd
struct MotorCmd{
    unsigned int mode;
    float q;
    float dq;
    float tau;
    float Kp;
    float Kd;

    MotorCmd(){
        mode = 0;
        q = 0;
        dq = 0;
        tau = 0;
        Kp = 0;
        Kd = 0;
    }
};

struct LowlevelCmd{
    //定义12个包含关节底层命令的结构体数组
    MotorCmd motorCmd[12];
    //将发送给四条腿的12个关节角度存入motorCmd
    void setQ(Vec12 q){
        for(int i(0); i<12; ++i){
            motorCmd[i].q = q(i);
        }
    }
    //将发送给legID号腿的3个关节角度存入motorCmd
    void setQ(int legID, Vec3 qi){
        motorCmd[legID*3+0].q = qi(0);
        motorCmd[legID*3+1].q = qi(1);
        motorCmd[legID*3+2].q = qi(2);
    }
    //将发送给四条腿的12个关节速度存入motorCmd
    void setQd(Vec12 qd){
        for(int i(0); i<12; ++i){
            motorCmd[i].dq = qd(i);
        }
    }
    //将发送给legID号腿的3个关节速度存入motorCmd
    void setQd(int legID, Vec3 qdi){
        motorCmd[legID*3+0].dq = qdi(0);
        motorCmd[legID*3+1].dq = qdi(1);
        motorCmd[legID*3+2].dq = qdi(2);
    }
    //将发送给各个关节电机的的前馈力矩进行限幅
    void setTau(Vec12 tau, Vec2 torqueLimit = Vec2(-50, 50)){
        for(int i(0); i<12; ++i){
            if(std::isnan(tau(i))){
                printf("[ERROR] The setTau function meets Nan\n");
            }
            motorCmd[i].tau = saturation(tau(i), torqueLimit);
        }
    }
    //将发送给legID号腿的三个关节速度置零
    void setZeroDq(int legID){
        motorCmd[legID*3+0].dq = 0;
        motorCmd[legID*3+1].dq = 0;
        motorCmd[legID*3+2].dq = 0;
    }
    //将发送给四条腿的12个关节速度置零
    void setZeroDq(){
        for(int i(0); i<4; ++i){
            setZeroDq(i);
        }
    }
    //将发送给legID号腿的三个关节前馈力矩置零
    void setZeroTau(int legID){
        motorCmd[legID*3+0].tau = 0;
        motorCmd[legID*3+1].tau = 0;
        motorCmd[legID*3+2].tau = 0;
    }
    //设置仿真下legID号站立腿的刚度系数
    void setSimStanceGain(int legID){
        motorCmd[legID*3+0].mode = 10;
        motorCmd[legID*3+0].Kp = 180;
        motorCmd[legID*3+0].Kd = 8;
        motorCmd[legID*3+1].mode = 10;
        motorCmd[legID*3+1].Kp = 180;
        motorCmd[legID*3+1].Kd = 8;
        motorCmd[legID*3+2].mode = 10;
        motorCmd[legID*3+2].Kp = 300;
        motorCmd[legID*3+2].Kd = 15;
    }
    //设置实机下legID号站立腿的刚度系数
    void setRealStanceGain(int legID){
        motorCmd[legID*3+0].mode = 10;
        motorCmd[legID*3+0].Kp = 60;
        motorCmd[legID*3+0].Kd = 5;
        motorCmd[legID*3+1].mode = 10;
        motorCmd[legID*3+1].Kp = 40;
        motorCmd[legID*3+1].Kd = 4;
        motorCmd[legID*3+2].mode = 10;
        motorCmd[legID*3+2].Kp = 80;
        motorCmd[legID*3+2].Kd = 7;
    }
    //将legID号腿的3个关节刚度系数置零
    void setZeroGain(int legID){
        motorCmd[legID*3+0].mode = 10;
        motorCmd[legID*3+0].Kp = 0;
        motorCmd[legID*3+0].Kd = 0;
        motorCmd[legID*3+1].mode = 10;
        motorCmd[legID*3+1].Kp = 0;
        motorCmd[legID*3+1].Kd = 0;
        motorCmd[legID*3+2].mode = 10;
        motorCmd[legID*3+2].Kp = 0;
        motorCmd[legID*3+2].Kd = 0;
    }
    //将四条腿的12个关节刚度系数置零
    void setZeroGain(){
        for(int i(0); i<4; ++i){
            setZeroGain(i);
        }
    }
    //设置接触腿刚度系数
    void setStableGain(int legID){
        motorCmd[legID*3+0].mode = 10;
        motorCmd[legID*3+0].Kp = 0.8;
        motorCmd[legID*3+0].Kd = 0.8;
        motorCmd[legID*3+1].mode = 10;
        motorCmd[legID*3+1].Kp = 0.8;
        motorCmd[legID*3+1].Kd = 0.8;
        motorCmd[legID*3+2].mode = 10;
        motorCmd[legID*3+2].Kp = 0.8;
        motorCmd[legID*3+2].Kd = 0.8;
    }
    void setStableGain(){
        for(int i(0); i<4; ++i){
            setStableGain(i);
        }
    }
    //设置摆动腿刚度系数
    void setSwingGain(int legID){
        motorCmd[legID*3+0].mode = 10;
        motorCmd[legID*3+0].Kp = 3;
        motorCmd[legID*3+0].Kd = 2;
        motorCmd[legID*3+1].mode = 10;
        motorCmd[legID*3+1].Kp = 3;
        motorCmd[legID*3+1].Kd = 2;
        motorCmd[legID*3+2].mode = 10;
        motorCmd[legID*3+2].Kp = 3;
        motorCmd[legID*3+2].Kd = 2;
    }
};

#endif  //LOWLEVELCMD_H