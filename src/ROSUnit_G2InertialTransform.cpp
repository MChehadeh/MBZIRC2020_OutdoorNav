//This is Global to Inertial Frame Transform Publisher

#include "ROSUnit_G2InertialTransform.hpp"
#include <iostream>

ROSUnit_G2InertialTransform* ROSUnit_G2InertialTransform::_instance_ptr = NULL;

//TODO to be done for GPS

ROSUnit_G2InertialTransform::ROSUnit_G2InertialTransform(ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler)
{
    _pub_transform = t_main_handler.advertise<geometry_msgs::PoseStamped>("/Transformed_Pose/OptitrackPose", 1000);
    _instance_ptr = this;
}

ROSUnit_G2InertialTransform::~ROSUnit_G2InertialTransform() {
}

void ROSUnit_G2InertialTransform::receive_msg_data(DataMessage* t_msg)
{

    if(t_msg->getType() == msg_type::POSITION)
    {
        data_to_send.pose.position.x = ((PositionMsg*)t_msg)->x;
        data_to_send.pose.position.y = ((PositionMsg*)t_msg)->y;
        data_to_send.pose.position.z = ((PositionMsg*)t_msg)->z;
    }
    if(t_msg->getType() == msg_type::ATTITUDE)
    {
        data_to_send.pose.orientation.x = ((AttitudeMsg*)t_msg)->pitch;
        data_to_send.pose.orientation.y = ((AttitudeMsg*)t_msg)->roll;
    }
    if (t_msg->getType() == msg_type::HEADING)
    {
        data_to_send.pose.orientation.z = ((HeadingMsg*)t_msg)->yaw;   
    }
    _pub_transform.publish(data_to_send); //TODO: This is wrong
}