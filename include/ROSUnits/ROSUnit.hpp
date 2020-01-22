#pragma once
#include "ros/ros.h"
#include <iostream>
#include <string>
#include "std_msgs/String.h"
#include "MsgReceiver.hpp"
#include "MsgEmitter.hpp"
#include "common_types.hpp"

const int ROSUnit_capacity=5;
class ROSUnit : public msg_emitter, public msg_receiver{

    private:
        ros::NodeHandle _main_handler;

    public:
        ros::NodeHandle getNodeHandle();
        virtual void receive_msg_data(DataMessage* t_msg) = 0;
    
        ROSUnit(ros::NodeHandle&);
        ~ROSUnit();
    protected:
        
        
};