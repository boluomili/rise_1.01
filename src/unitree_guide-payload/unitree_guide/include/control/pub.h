#ifndef PUB_H
#define PUB_H

#include "ros/ros.h"
#include "std_msgs/String.h" 
#include <std_msgs/Float64.h>
#include "unitree_guide/publish_movement.h"
#include "unitree_guide/publish_turning.h"
#include "common/mathTypes.h"
#include "unitree_guide/publish_rise.h"

class Pub
{
private:
    ros::NodeHandle _nh;// NodeHandle
    ros::Publisher pub_mp;// mp
    ros::Publisher pub_movement;// Movement Data
    ros::Publisher pub_turning;// Turning Data
    std_msgs::Float64 data_mp;// mp msgs
    unitree_guide::publish_movement data_movement;// movement msgs
    unitree_guide::publish_turning data_turning;// turning msgs
    //**********8.30**************
    ros::Publisher pub_rise;
    ros::Subscriber sub_rise;
    unitree_guide::publish_rise data_rise;
    //**********8.30**************
public:
    // 构造函数，初始化发布者（确定话题名称及队列长度）
    Pub();
    // 析构函数，空实现
    ~Pub();
    // 发布估计负载质量
    void pub_data_mp(double _mp);
    // 发布机身位置、速度、加速度、足端力之和等消息
    void pub_data_movement(Vec3 p, Vec3 p_d, Vec3 v, Vec3 v_d, Vec3 a, Vec3 a_d, double sumfootforce , double d_mp, Vec3 err_p, Vec3 err_v,double pos_error_0);//重载了位置误差版本
        void pub_data_movement(Vec3 p, Vec3 p_d, Vec3 v, Vec3 v_d, Vec3 a, Vec3 a_d, double sumfootforce , double d_mp, Vec3 err_p, Vec3 err_v);
    // 发布机身方向、角速度、干扰项d、辅助变量更新律dkexi、转矩输出U
    void pub_data_turning(Vec3 q, Vec3 q_d, Vec3 w, Vec3 w_d, Vec3 err_q, Vec3 err_w, Vec3 disturbance, Vec3 dkexi, Vec3 U);
    // 发布位置误差，速度误差，复合误差e2，e2（0），积分项，miu_t的值，sgn的取值，miu_T/9.81;
    void pub_data_rise(Vec3 posError,Vec3 velError,Vec3 Error2,Vec3 Error2_0,Vec3 intergral,Vec3 miu_t,Vec3 templesgn,Vec3 templemiu);
    //回调函数
    //void sub_data_rise(double data1,double data2,double data3,double data4);

    void chatterCallback(const unitree_guide::publish_rise& msg);
    void sub_data_rise(double &data1,double &data2,double &data3,double &data4);


};

#endif