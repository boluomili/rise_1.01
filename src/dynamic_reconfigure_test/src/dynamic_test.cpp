#include <ros/ros.h>
#include "std_msgs/String.h"
#include <dynamic_reconfigure/server.h>
#include <dynamic_reconfigure_test/pidConfig.h>
#include "unitree_guide/publish_rise.h"
 
float KP = 0.5;
float KI = 20;
float KD = 31.5;
float KE = 20;
 
 
//回调函数
void Callback(dynamic_reconfigure_test::pidConfig &config)
{
    KP = config.KP;
    KI = config.KI;
    KD = config.KD;
    KE = config.KE;
 
    ROS_INFO("KP KI KD = [%f %f %f]",KP,KI,KD);
}
 
 
int main(int argc,char **argv)
{
    //初始化，创建节点
    ros::init(argc,argv,"dynamic_test");
 
    ros::NodeHandle n;
    ros::Publisher chatter_pub=n.advertise<unitree_guide::publish_rise>("chatter",1000);
    ros::Rate loop_rate(10);
      int count = 0;
          //创建一个参数动态配置的服务器实例
    dynamic_reconfigure::Server<dynamic_reconfigure_test::pidConfig> server;
    //定义回调函数
    dynamic_reconfigure::Server<dynamic_reconfigure_test::pidConfig>::CallbackType f;
 
while (ros::ok())
  {
    unitree_guide::publish_rise msg;
    
    f = boost::bind(&Callback,_1);
    server.setCallback(f);
    msg.data1=KP;
    msg.data2=KI;
    msg.data3=KD;
    msg.data4=KE;
    chatter_pub.publish(msg);
   
    ros::spinOnce();
 
    loop_rate.sleep();
    ++count;
  }



    //将回调函数和服务端绑定，当客户端请求修改参数时，服务器跳转到回调函数进行处理

 
    
 
    return 0;
}