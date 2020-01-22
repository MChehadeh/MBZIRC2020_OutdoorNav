#pragma once
#include "ros/ros.h"
#include <geometry_msgs/Vector3Stamped.h>
#include <geometry_msgs/QuaternionStamped.h>
#include "ROSUnit.hpp"
#include "Vector3D.hpp"
#include "Quaternion.hpp"
#include "AttitudeMsg.hpp"
#include "VelocityMsg.hpp"
#include "HeadingMsg.hpp"
#include "PositionMsg.hpp"
#include "AccelerationMsg.hpp"

class ROSUnit_Xsens : public ROSUnit{

    private:
        static ROSUnit_Xsens* _instance_ptr;
        ros::Subscriber _sub_attitude;
        ros::Subscriber _sub_position;
        ros::Subscriber _sub_velocity;
        static AttitudeMsg attitude_msg;
        static VelocityMsg velocity_msg; 
        static HeadingMsg heading_msg; 
        static PositionMsg position_msg; 
        static AccelerationMsg acceleration_msg;  
        static void callbackXsensPosition(const geometry_msgs::Vector3Stamped& msg_position);
        static void callbackXsensAttitude(const geometry_msgs::QuaternionStamped& msg_attitude);
        static void callbackXsensVelocity(const geometry_msgs::Vector3Stamped& msg_velocity);
        void receive_msg_data(DataMessage* t_msg);  
        
    public:
        ROSUnit_Xsens(ros::NodeHandle&);
        ~ROSUnit_Xsens();

};