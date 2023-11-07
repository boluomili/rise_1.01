#include "control/pub.h"
#include <ros/ros.h>
#include "unitree_guide/publish_rise.h"

Pub::Pub(){
    pub_mp = _nh.advertise<std_msgs::Float64>("/mp",1);
    pub_movement = _nh.advertise<unitree_guide::publish_movement>("/mdata_movement",20);
    pub_turning = _nh.advertise<unitree_guide::publish_turning>("/mdata_turning",20);
    //****************8.30**************
    pub_rise = _nh.advertise<unitree_guide::publish_rise>("/mdata_rise",20);
    sub_rise=_nh.subscribe("chatter",1000,&Pub::chatterCallback,this);
    //pub_turning = _nh.advertise<unitree_guide::publish_turning>("/mdata_turning",20);
    //****************8.30**************
}

Pub::~Pub(){

}
// 发布估计负载质量
void Pub::pub_data_mp(double _mp){
    data_mp.data = _mp; 
    pub_mp.publish(data_mp);
}
// 发布机身位置、速度、加速度、足端力之和等消息
void Pub::pub_data_movement(Vec3 p, Vec3 p_d, Vec3 v, Vec3 v_d, Vec3 a, Vec3 a_d, double sumfootforce, double d_mp, Vec3 err_p, Vec3 err_v,double pos_error_0){
    for (int i = 0; i < 3; i++)
    {
        data_movement.p[i]   = p[i];
        data_movement.p_d[i] = p_d[i];
        data_movement.err_p[i] = err_p[i];
        data_movement.v[i]   = v[i];
        data_movement.v_d[i] = v_d[i];
        data_movement.err_v[i] = err_v[i];
        data_movement.a[i]   = a[i];
        data_movement.a_d[i] = a_d[i];
        data_movement.pos_error_0=pos_error_0;
    }
    data_movement.sumfootforce = sumfootforce;
    data_movement.d_mp = d_mp;
    pub_movement.publish(data_movement);
}
void Pub::pub_data_movement(Vec3 p, Vec3 p_d, Vec3 v, Vec3 v_d, Vec3 a, Vec3 a_d, double sumfootforce, double d_mp, Vec3 err_p, Vec3 err_v){
    for (int i = 0; i < 3; i++)
    {
        data_movement.p[i]   = p[i];
        data_movement.p_d[i] = p_d[i];
        data_movement.err_p[i] = err_p[i];
        data_movement.v[i]   = v[i];
        data_movement.v_d[i] = v_d[i];
        data_movement.err_v[i] = err_v[i];
        data_movement.a[i]   = a[i];
        data_movement.a_d[i] = a_d[i];
       
    }
    data_movement.sumfootforce = sumfootforce;
    data_movement.d_mp = d_mp;
    pub_movement.publish(data_movement);
}




// 发布机身方向、角速度、干扰项d、辅助变量更新律dkexi、转矩输出U
void Pub::pub_data_turning(Vec3 q, Vec3 q_d, Vec3 w, Vec3 w_d, Vec3 err_q, Vec3 err_w, Vec3 disturbance, Vec3 dkexi, Vec3 U){
    for (int i = 0; i < 3; i++)
    {
        data_turning.q[i]      = q[i];
        data_turning.q_d[i]    = q_d[i];
        data_turning.w[i]      = w[i];
        data_turning.w_d[i]    = w_d[i];
        data_turning.err_q[i]  = err_q[i];
        data_turning.err_w[i]  = err_w[i];
        data_turning.disturbance[i]   = disturbance[i];
        data_turning.dkexi[i]  = dkexi[i];
        data_turning.U[i] = U[i];
        
    }
    pub_turning.publish(data_turning);
}

void Pub::pub_data_rise(Vec3 posError,Vec3 velError,Vec3 Error2,Vec3 Error2_0,Vec3 intergral,Vec3 miu_t,Vec3 templesgn,Vec3 templemiu){
        for (int i = 0; i < 3; i++)
    {
        data_rise.posError[i]      = posError[i];
        data_rise.velError[i]    = velError[i];
        data_rise.Error2[i]     = Error2[i];
        data_rise.Error2_0[i]    = Error2_0[i];
        data_rise.intergral[i]  = intergral[i];
        data_rise.miu_t[i]  = miu_t[i];
        data_rise.templesgn[i]   = templesgn[i];
        data_rise.templemiu[i] = templemiu[i];
        
    }
    pub_rise.publish(data_rise);
}


//订阅的回调函数，把发出的msg赋值到data_rise装住
void Pub::chatterCallback(const unitree_guide::publish_rise & msg){
                data_rise.data1=msg.data1;
                data_rise.data2=msg.data2;
                data_rise.data3=msg.data3;
                data_rise.data4=msg.data4;



    ROS_INFO("data1:%0.6f,data2:%0.6f,data3:%0.6f", msg.data1,msg.data2,msg.data3);
}
//将临时存储的data_rise赋值给K_s,beita,alphe2,alphe2。
void Pub::sub_data_rise(double &data1,double &data2,double &data3,double &data4){
        
        data1=data_rise.data1;
        data2=data_rise.data2;
        data3=data_rise.data3;
        data4=data_rise.data4;
}
