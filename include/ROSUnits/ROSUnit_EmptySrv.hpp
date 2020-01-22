#pragma once

#include "ROSUnit.hpp"
#include "std_srvs/Empty.h"
//Change the msg type to match your received msg
#include "EmptyMsg.hpp"

class ROSUnit_EmptySrv : public ROSUnit
{
    public:
    
        ROSUnit_EmptySrv(std::string, ros::NodeHandle&);
        ~ROSUnit_EmptySrv();
        void receive_msg_data(DataMessage* t_msg) {};

    private:

    ros::ServiceServer m_server;
    static int internal_counter;
    static ROSUnit_EmptySrv* m_ptr[ROSUnit_capacity];
    //Change the srv_callback code to reflect your system
    static bool(*callbackFunctionPointer[ROSUnit_capacity])(std_srvs::Empty::Request&, std_srvs::Empty::Response&);
    static bool srv_callback1(std_srvs::Empty::Request&, std_srvs::Empty::Response&);//TODO refactor through templates
    static bool srv_callback2(std_srvs::Empty::Request&, std_srvs::Empty::Response&);
    static bool srv_callback3(std_srvs::Empty::Request&, std_srvs::Empty::Response&);
    static bool srv_callback4(std_srvs::Empty::Request&, std_srvs::Empty::Response&);
    static bool srv_callback5(std_srvs::Empty::Request&, std_srvs::Empty::Response&);

};