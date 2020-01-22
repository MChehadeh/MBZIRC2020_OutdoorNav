#pragma once

#include "ROSUnit.hpp"
#include "std_msgs/Float32.h"
//Change the msg type to match your received msg
#include "FloatMsg.hpp"

class ROSUnit_FloatSub : public ROSUnit
{
    public:

        ROSUnit_FloatSub(std::string, ros::NodeHandle&);
        ~ROSUnit_FloatSub();
        void receive_msg_data(DataMessage* t_msg) {};

    private:

        ros::Subscriber m_sub;
        static int internal_counter;
        static ROSUnit_FloatSub* m_ptr[ROSUnit_capacity];
        //Change the callback code to reflect your system
        //static void callback(const std_msgs::Float32::ConstPtr&);
        static void(*callbackFunctionPointer[ROSUnit_capacity])(const std_msgs::Float32::ConstPtr&);
        static void callback1(const std_msgs::Float32::ConstPtr&);//TODO refactor through templates
        static void callback2(const std_msgs::Float32::ConstPtr&);
        static void callback3(const std_msgs::Float32::ConstPtr&);
        static void callback4(const std_msgs::Float32::ConstPtr&);
        static void callback5(const std_msgs::Float32::ConstPtr&);

};