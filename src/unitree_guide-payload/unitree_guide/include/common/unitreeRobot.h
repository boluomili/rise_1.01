/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#ifndef UNITREEROBOT_H
#define UNITREEROBOT_H

#include "common/unitreeLeg.h"
#include "message/LowlevelState.h"
//整机运动学、静力学相关计算的类
class QuadrupedRobot{
public:
    QuadrupedRobot(){};
    ~QuadrupedRobot(){}

    Vec3 getX(LowlevelState &state);
    Vec34 getVecXP(LowlevelState &state);

    // Inverse Kinematics(Body/Hip Frame)
    Vec12 getQ(const Vec34 &feetPosition, FrameType frame);//获取Frame坐标系下12个关节角
    Vec12 getQd(const Vec34 &feetPosition, const Vec34 &feetVelocity, FrameType frame);//获取frame坐标系下12个关节角速度
    Vec12 getTau(const Vec12 &q, const Vec34 feetForce);//机器人静力学计算，获取机器人的12个关节力矩

    // Forward Kinematics
    Vec3 getFootPosition(LowlevelState &state, int id, FrameType frame);//获取足端在frame坐标系下的位置向量
    Vec3 getFootVelocity(LowlevelState &state, int id);//获取当前状态下足端速度
    Vec34 getFeet2BPositions(LowlevelState &state, FrameType frame);//获取足端相对于机身中心的位置向量
    Vec34 getFeet2BVelocities(LowlevelState &state, FrameType frame);//获取足端相对于机身中心的速度向量

    Mat3 getJaco(LowlevelState &state, int legID);//获取第legID条腿的雅可比矩阵
    Vec2 getRobVelLimitX(){return _robVelLimitX;}//机身坐标系{b}下x轴方向的平移速度区间
    Vec2 getRobVelLimitY(){return _robVelLimitY;}//机身坐标系{b}下y轴方向的平移速度区间
    Vec2 getRobVelLimitYaw(){return _robVelLimitYaw;}//机身坐标系{b}下绕z轴方向的转动角速度区间
    Vec34 getFeetPosIdeal(){return _feetPosNormalStand;}//各个足端中性落足点在机身坐标系{b}下的坐标
    double getRobMass(){return _mass;}//获取机器人的质量
    Vec3 getPcb(){return _pcb;}
    Mat3 getRobInertial(){return _Ib;}//获取机器人惯性矩阵

protected:
    QuadrupedLeg* _Legs[4];//每个元素都是一个QuadrupedLeg类指针，代表四条腿
    Vec2 _robVelLimitX;//x轴方向平移速度区间
    Vec2 _robVelLimitY;//y轴方向平移速度区间
    Vec2 _robVelLimitYaw;//机身坐标系{b}下绕z轴方向的转动角速度区间
    Vec34 _feetPosNormalStand;
    double _mass;//机器人简化模型的质量
    Vec3 _pcb;
    Mat3 _Ib;//机器人简化模型在机身坐标系下的转动惯量
};

class A1Robot : public QuadrupedRobot{
public:
    A1Robot();
    ~A1Robot(){}
};

class Go1Robot : public QuadrupedRobot{
public:
    Go1Robot();
    ~Go1Robot(){};
};

#endif  // UNITREEROBOT_H