#include "ROSUnit_RTK2.hpp"
#include <iostream>
ROSUnit_RTK2* ROSUnit_RTK2::_instance_ptr = NULL;
RTKMessagePosition ROSUnit_RTK2::rtk_msg_position;
RTKMessageVelocity ROSUnit_RTK2::rtk_msg_velocity;


ROSUnit_RTK2::ROSUnit_RTK2(ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler){
    _sub_fix2 = t_main_handler.subscribe("r2/tcpfix", 10, callbackRTKPosition2);
    _sub_vel2 = t_main_handler.subscribe("r2/tcpvel", 10, callbackRTKVelocity2);
    _instance_ptr = this;
}

ROSUnit_RTK2::~ROSUnit_RTK2() {

}

void ROSUnit_RTK2::callbackRTKPosition2(const sensor_msgs::NavSatFix::ConstPtr & msg){
    
    Vector3D<double> pos_data;
    pos_data.x = msg->latitude;
    pos_data.y = msg->longitude;
    pos_data.z = msg->altitude;

    rtk_msg_position.position.x=pos_data.x;
    rtk_msg_position.position.y=pos_data.y;
    rtk_msg_position.position.z=pos_data.z;
    rtk_msg_position.id=2;
    _instance_ptr->emit_message((DataMessage*) &rtk_msg_position);

}


void ROSUnit_RTK2::callbackRTKVelocity2(const geometry_msgs::TwistStamped::ConstPtr& msg){
    
    Vector3D<double> vel_data;
    vel_data.x = msg->twist.linear.x;
    vel_data.y = msg->twist.linear.y;
    vel_data.z = msg->twist.linear.z;

   
    rtk_msg_velocity.velocity.x=vel_data.x;
    rtk_msg_velocity.velocity.y=vel_data.y;
    rtk_msg_velocity.velocity.z=vel_data.z;
    _instance_ptr->emit_message((DataMessage*) &rtk_msg_velocity); 
    
    
}

void ROSUnit_RTK2::receive_msg_data(DataMessage* t_msg){


}