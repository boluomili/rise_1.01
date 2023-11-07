/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#ifndef UNITREELEG_H
#define UNITREELEG_H

#include "common/mathTypes.h"
#include "common/enumClass.h"
//四足机器人的腿类，主要实现单条腿的正、逆运动学计算，一阶微分正、逆运算，静力学计算
class QuadrupedLeg{
public:
    QuadrupedLeg(int legID, float abadLinkLength, float hipLinkLength, 
                 float kneeLinkLength, Vec3 pHip2B);
    ~QuadrupedLeg(){}
    Vec3 calcPEe2H(Vec3 q);//计算在腿基座坐标系{0}下的足端位置
    Vec3 calcPEe2B(Vec3 q);//计算在机身中心坐标系下的足端位置
    Vec3 calcVEe(Vec3 q, Vec3 qd);//计算足端速度
    Vec3 calcQ(Vec3 pEe, FrameType frame);//计算在frame坐标系下的关节角
    Vec3 calcQd(Vec3 q, Vec3 vEe);//计算在当前关节角及足端速度下的关节角速度
    Vec3 calcQd(Vec3 pEe, Vec3 vEe, FrameType frame);//计算在frame坐标系下的足端位置和足端速度的关节角速度
    Vec3 calcTau(Vec3 q, Vec3 force);//计算当前关节角和足端作用力对应的关节力矩
    Mat3 calcJaco(Vec3 q);//计算当前关节角下的雅可比矩阵
    Vec3 getHip2B(){return _pHip2B;}//获取机身中心到腿基座坐标系{0}原点的向量
protected:
    float q1_ik(float py, float pz, float b2y);//(逆运动学求关节角theta1)
    float q3_ik(float b3z, float b4z, float b);//(逆运动学求关节角theta1)
    float q2_ik(float q1, float q3, float px, 
                float py, float pz, float b3z, float b4z);//(逆运动学求关节角theta3)
    float _sideSign;
    const float _abadLinkLength, _hipLinkLength, _kneeLinkLength;//髋、大腿、小腿连杆长度
    const Vec3 _pHip2B;//机身中心到腿基座坐标系{0}原点的向量
};
//继承四足机器人的腿类 QuadrupedLeg，实现A1的腿部相关运算
class A1Leg : public QuadrupedLeg{
public:
    A1Leg(const int legID, const Vec3 pHip2B):
        QuadrupedLeg(legID, 0.0838, 0.2, 0.2, pHip2B){}
    ~A1Leg(){}
};
//继承四足机器人的腿类 QuadrupedLeg，实现GO1的腿部相关运算
class Go1Leg : public QuadrupedLeg{
public:
    Go1Leg(const int legID, const Vec3 pHip2B):
        QuadrupedLeg(legID, 0.08, 0.213, 0.213, pHip2B){}
    ~Go1Leg(){}
};

#endif  // UNITREELEG_H