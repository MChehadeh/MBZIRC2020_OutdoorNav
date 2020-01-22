#include "ROSUnit_Xsens.hpp"
#include <iostream>
ROSUnit_Xsens* ROSUnit_Xsens::_instance_ptr = NULL;
AttitudeMsg ROSUnit_Xsens::attitude_msg;
VelocityMsg ROSUnit_Xsens::velocity_msg;
HeadingMsg ROSUnit_Xsens::heading_msg;
PositionMsg ROSUnit_Xsens::position_msg;

AccelerationMsg ROSUnit_Xsens::acceleration_msg;

ROSUnit_Xsens::ROSUnit_Xsens(ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler){
    _sub_attitude = t_main_handler.subscribe("filter/quaternion", 10, callbackXsensAttitude);
    _sub_position = t_main_handler.subscribe("filter/positionlla", 10, callbackXsensPosition);
    _sub_velocity = t_main_handler.subscribe("filter/velocity", 10, callbackXsensVelocity);
    _instance_ptr = this;
}

ROSUnit_Xsens::~ROSUnit_Xsens() {

}

void ROSUnit_Xsens::callbackXsensPosition(const geometry_msgs::Vector3Stamped& msg_position){
    
    Vector3D<float> pos_data;
    pos_data.x = msg_position.vector.x;
    pos_data.y = msg_position.vector.y;
    pos_data.z = msg_position.vector.z;

    position_msg.x=pos_data.x;
    position_msg.y=pos_data.y;
    position_msg.z=pos_data.z;
    _instance_ptr->emit_message((DataMessage*) &position_msg);
}
void ROSUnit_Xsens::callbackXsensAttitude( const geometry_msgs::QuaternionStamped& msg_attitude){
    Quaternion att_data;
    // cout<<"ROSUnit"<<endl;
    att_data.x = msg_attitude.quaternion.x;
    att_data.y = msg_attitude.quaternion.y;
    att_data.z = msg_attitude.quaternion.z;
    att_data.w = msg_attitude.quaternion.w;

//Convert Quaternion to euler
    Vector3D<float> _euler;

    double sinr_cosp = +2.0 * ( att_data.w * att_data.x + att_data.y * att_data.z);
    double cosr_cosp = +1.0 - 2.0 * (att_data.x * att_data.x + att_data.y * att_data.y);
    _euler.x = atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = +2.0 * ( att_data.w * att_data.y - att_data.z * att_data.x);
    if (fabs(sinp) >= 1)
        _euler.y = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    else
        _euler.y = asin(sinp);

    // yaw (z-axis rotation)
    double siny_cosp = +2.0 * ( att_data.w * att_data.z + att_data.x * att_data.y);
    double cosy_cosp = +1.0 - 2.0 * (att_data.y * att_data.y + att_data.z * att_data.z );  
    _euler.z= atan2(siny_cosp, cosy_cosp);



    attitude_msg.pitch=_euler.x;
    attitude_msg.roll=_euler.y;
    heading_msg.yaw=_euler.z;
    // cout << _euler.x<< endl;
    _instance_ptr->emit_message((DataMessage*) &attitude_msg);    
    _instance_ptr->emit_message((DataMessage*) &heading_msg); 
}
void ROSUnit_Xsens::callbackXsensVelocity(const geometry_msgs::Vector3Stamped& msg_velocity){
   
    Vector3D<float> vel_data;
    vel_data.x = msg_velocity.vector.x;
    vel_data.y = msg_velocity.vector.y;
    vel_data.z = msg_velocity.vector.z;


    ros::Time t_time = msg_velocity.header.stamp;

    double t_dt = t_time.toSec();

    
    velocity_msg.dx=vel_data.x;
    velocity_msg.dy=vel_data.y;
    velocity_msg.dz=vel_data.z;
    _instance_ptr->emit_message((DataMessage*) &velocity_msg); 
}

void ROSUnit_Xsens::receive_msg_data(DataMessage* t_msg){

}