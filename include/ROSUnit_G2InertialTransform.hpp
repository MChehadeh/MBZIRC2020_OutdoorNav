#pragma once
#include "ros/ros.h"
#include <geometry_msgs/PoseStamped.h>
#include "ROSUnit.hpp"
#include "Vector3D.hpp"
#include "PositionMsg.hpp"
#include "AttitudeMsg.hpp"
#include "HeadingMsg.hpp"

class ROSUnit_G2InertialTransform : public ROSUnit{

    private:
        static ROSUnit_G2InertialTransform* _instance_ptr;
        ros::Publisher _pub_transform;
        static void callbackTransform(const geometry_msgs::PoseStamped& msg);
        void receive_msg_data(DataMessage* t_msg);
        geometry_msgs::PoseStamped data_to_send;
  
    public:
        ROSUnit_G2InertialTransform(ros::NodeHandle&);
        ~ROSUnit_G2InertialTransform();

}; 