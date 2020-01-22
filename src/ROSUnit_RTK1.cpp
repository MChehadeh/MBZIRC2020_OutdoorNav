#include "ROSUnit_RTK1.hpp"
#include <iostream>
ROSUnit_RTK1* ROSUnit_RTK1::_instance_ptr = NULL;
RTKMessagePosition ROSUnit_RTK1::rtk_msg_position;
RTKMessageVelocity ROSUnit_RTK1::rtk_msg_velocity;



ROSUnit_RTK1::ROSUnit_RTK1(ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler){
  _sub_fix1 = t_main_handler.subscribe("r1/tcpfix", 10, callbackRTKPosition1);
  _sub_vel1 = t_main_handler.subscribe("r1/tcpvel", 10, callbackRTKVelocity1);
  _instance_ptr = this;
}

ROSUnit_RTK1::~ROSUnit_RTK1() {

}

void ROSUnit_RTK1::callbackRTKPosition1(const sensor_msgs::NavSatFix::ConstPtr & msg){
    
    Vector3D<double> pos_data;
    pos_data.x = msg->latitude;
    pos_data.y = msg->longitude;
    pos_data.z = msg->altitude;

    rtk_msg_position.position.x=pos_data.x;
    rtk_msg_position.position.y=pos_data.y;
    rtk_msg_position.position.z=pos_data.z;
    rtk_msg_position.id=1;
    _instance_ptr->emit_message((DataMessage*) &rtk_msg_position);
}


void ROSUnit_RTK1::callbackRTKVelocity1(const geometry_msgs::TwistStamped::ConstPtr& msg){
    
    Vector3D<double> vel_data;
    vel_data.x = msg->twist.linear.x;
    vel_data.y = msg->twist.linear.y;
    vel_data.z = msg->twist.linear.z;

   
    rtk_msg_velocity.velocity.x=vel_data.x;
    rtk_msg_velocity.velocity.y=vel_data.y;
    rtk_msg_velocity.velocity.z=vel_data.z;
    rtk_msg_position.id=1;
    _instance_ptr->emit_message((DataMessage*) &rtk_msg_velocity); 
}        

void ROSUnit_RTK1::receive_msg_data(DataMessage* t_msg){


}