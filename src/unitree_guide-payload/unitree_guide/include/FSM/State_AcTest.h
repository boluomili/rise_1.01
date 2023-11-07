/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#ifndef ACTEST_H
#define ACTEST_H

#include "FSM/FSMState.h"
#include "Gait/GaitGenerator.h"
#include "control/BalanceCtrl.h"
#include<dynamic_reconfigure/server.h>
#include<unitree_guide/riseConfig.h>
#include <ros/ros.h>

class State_AcTest : public FSMState{
public:
    State_AcTest(CtrlComponents *ctrlComp);
    ~State_AcTest();
    void enter();
    void run();
    void exit();
    virtual FSMStateName checkChange();
    //设置高层速度命令
    void setHighCmd(double vx, double vy, double wz);
    //******************8.28.19***************************
    //sgn函数的设计
    int sgn(double val);

    //void Callback(dynamic_reconfigure_test::riseConfig &config);
   

    double setK_s_value(double value){
        return value;
    }
    void set_beita_value(double value){
        _beita=value;
    }
    void setalphe1_value(double value){
        alphe1=value;
    }
    void setalphe2_value(double value){
        alphe2=value;
    }
        double setK_s_value()const{
        return K_s;
    }
    double set_beita_value()const{
        return _beita;
    }
    double setalphe1_value()const{
        return alphe1;
    }
    double setalphe2_value()const{
        return alphe2;
    }
    
    //******************8.28.19***************************
private:
    //计算足端力，支撑腿的足端力由平衡控制器计算得到，摆动腿的足端力由修正力（PD control）产生
    void calcTau();
    //根据目标足端位置和速度计算各个关节的角度和角速度
    void calcQQd();
    //计算世界坐标系{S}下的目标速度_vCmdGlobal、目标姿态_Rd、目标角速度_wCmdGlobal
    void calcCmd();
    //获取用户输入命令
    virtual void getUserCmd();
    void calcBalanceKp();
    //判断踏步还是四足站立
    bool checkStepOrNot();

    //当前足端位置
    Vec34 _Pi;
    //倾角；
    double _SlopeAngle;
    //第一次运行标志位
    bool _firstRun;
    //生成足端轨迹，计算足端目标位置、目标速度
    GaitGenerator *_gait;
    //状态估计器，计算机器人机身、足端的位置和速度
    Estimator *_est;
    //机器人模型，含机器人运动学及静力学计算、关节力矩、位置、速度命令
    QuadrupedRobot *_robModel;
    //平衡控制器，计算期望的足端力
    BalanceCtrl *_balCtrl;
    //发布消息
    Pub *_pub;

    /* Rob State */
    Vec3  _posBody, _velBody;//机身位置、速度
    double _yaw, _dYaw;//机身偏航角、偏航角速度
    Vec34 _posFeetGlobal, _velFeetGlobal;//足端位置、速度
    Vec34 _posFeet2BGlobal;//足端相对于机身中心的位置
    RotMat _B2G_RotMat, _G2B_RotMat;//描述机身姿态的旋转矩阵、及其转置矩阵
    Vec12 _q;//各个关节角

    /* Robot command */
    Vec3 _pcd;//机身位置
    Vec3 _vCmdGlobal, _vCmdBody;//世界坐标系下{S}的机身目标速度、机身坐标系下{B}的机身目标速度、
    double _yawCmd, _dYawCmd;//目标偏航角、偏航角速度
    double _dYawCmdPast;
    Vec3 _wCmdGlobal;//旋转角速度向量
    Vec34 _posFeetGlobalGoal, _velFeetGlobalGoal;//目标足端位置、速度
    Vec34 _posFeet2BGoal, _velFeet2BGoal;//目标足端位置、速度（机身坐标系下）
    RotMat _Rd;//机身目标姿态的旋转矩阵
    Vec3 _ddPcd, _dWbd;//目标线加速度、角加速度
    Vec34 _forceFeetGlobal, _forceFeetBody;//机身坐标系下的目标足端力
    Vec34 _qGoal, _qdGoal;//期望关节角、关节速度
    Vec12 _tau;//各关节前馈力矩

    // Control Parameters
    double _gaitHeight;//摆动腿抬腿高度
    Vec3 _posError, _velError;
    //平衡控制器参数
    Mat3 _Kpp, _Kdp, _Kdw;
    double _kpw;
    //摆动腿足端修正力刚度、阻尼系数
    Mat3 _KpSwing, _KdSwing;
    //机身坐标系下X、Y平移，绕Z轴旋转速度区间
    Vec2 _vxLim, _vyLim, _wyawLim;
    Vec4 *_phase;
    VecInt4 *_contact;

    double _lamda;
    double _mb,_d_mb;//估计的负载质量
    Vec3 _S_Compound;
    Vec3 _Loading;//估计的负载
    double _Gammam;
    Vec3 _Ym;
    Mat3 _KD;

    int count = 0;
    Mat3 _lamdaTu;
    Vec3 _S_CompoundTu;
    Mat3 _GammaTu;
    Vec3 _YmTu;
    Mat3 _KDTu;
    Vec3 _Tu;//估计的负载转矩
    Vec3 _Tb;
    Vec3 _kexi;
    Vec3 _dkexi;
    Vec3 _U;
    Mat3 _E;

//******************8.28.19***************************
    Vec3 _error1;
    Vec3 _dderror1;
    Vec3 _error2;
    Vec3 _error2_0;
    Vec3 _r;
    Vec3 pos_integral;
    Vec3 pos_integral_d;
    int count_1;

    double K_s;
    double _beita;
    double alphe1;
    double alphe2;
    Vec3 miu_t;
    Vec3 dmiu_t;
    Vec3 integral;
    double beita;
    Vec3 templesgn;
    double outputmass;

    double param_1;
    double param_2;
    double param_3;
    double param_4;
    
//******************8.28.19***************************

    int _num;

    Eigen::Matrix<double, 4 , 3 > _YM;
    Eigen::Matrix<double, 4 , 1 > _ZM;
    Vec3 _Angle;
    Vec3 _dAngle;
    double _lastxposition;

    // Calculate average value
    AvgCov *_avg_posError = new AvgCov(3, "_posError", true, 1000, 1000, 1);
    AvgCov *_avg_angError = new AvgCov(3, "_angError", true, 1000, 1000, 1000);


};


#endif  // ACTEST_H