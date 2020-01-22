#pragma once
#include "ros/ros.h"
#include <geometry_msgs/PoseStamped.h>
#include "ROSUnit.hpp"
#include "Vector3D.hpp"
#include "OptitrackMessage.hpp"

class ROSUnit_Optitrack : public ROSUnit{

    private:
        static ROSUnit_Optitrack* _instance_ptr;
        ros::Subscriber _sub_attitude;
        static OptitrackMessage optitrack_msg; 
        static void callbackOptitrack(const geometry_msgs::PoseStamped& msg);
        void receive_msg_data(DataMessage* t_msg);
        
    public:
        ROSUnit_Optitrack(ros::NodeHandle&);
        ~ROSUnit_Optitrack();

};