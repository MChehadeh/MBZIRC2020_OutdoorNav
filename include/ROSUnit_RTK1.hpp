#pragma once
#include "ros/ros.h"
#include <sensor_msgs/NavSatFix.h>
#include <geometry_msgs/TwistStamped.h>
#include "ROSUnit.hpp"
#include "Vector3D.hpp"
#include "common_types.hpp"
#include "RTKMessagePosition.hpp"
#include "RTKMessageVelocity.hpp"

class ROSUnit_RTK1 : public ROSUnit{

    private:
        static ROSUnit_RTK1* _instance_ptr;
        static RTKMessagePosition rtk_msg_position;
        static RTKMessageVelocity rtk_msg_velocity;
        ros::Subscriber _sub_fix1;
        ros::Subscriber _sub_vel1;
        static void callbackRTKPosition1(const sensor_msgs::NavSatFix::ConstPtr & msg);
        static void callbackRTKVelocity1(const geometry_msgs::TwistStamped::ConstPtr& msg);
        void receive_msg_data(DataMessage* t_msg);  
        
    public:
        ROSUnit_RTK1(ros::NodeHandle&);
        ~ROSUnit_RTK1();

};