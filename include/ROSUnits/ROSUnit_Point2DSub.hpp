#pragma once

#include "ROSUnit.hpp"
#include "common_srv/Point2D.h"
//Change the msg type to match your received msg
#include "Vector2DMsg.hpp"

class ROSUnit_Point2DSub : public ROSUnit
{
    public:

        ROSUnit_Point2DSub(std::string, ros::NodeHandle&);
        ~ROSUnit_Point2DSub();
        void receive_msg_data(DataMessage* t_msg) {};

    private:

        ros::Subscriber m_sub;
        static int internal_counter;
        static ROSUnit_Point2DSub* m_ptr[ROSUnit_capacity];
        //Change the callback code to reflect your system
        //static void callback(const common_srv::Point2D::ConstPtr&);
        static void(*callbackFunctionPointer[ROSUnit_capacity])(const common_srv::Point2D::ConstPtr&);
        static void callback1(const common_srv::Point2D::ConstPtr&);//TODO refactor through templates
        static void callback2(const common_srv::Point2D::ConstPtr&);
        static void callback3(const common_srv::Point2D::ConstPtr&);
        static void callback4(const common_srv::Point2D::ConstPtr&);
        static void callback5(const common_srv::Point2D::ConstPtr&);
};