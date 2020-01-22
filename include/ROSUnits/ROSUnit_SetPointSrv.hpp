#pragma once

#include "ROSUnit.hpp"
#include "common_srv/set_point.h"
//Change the msg type to match your received msg
#include "Vector3DMessage.hpp"

class ROSUnit_SetPointSrv : public ROSUnit
{
public:

    ROSUnit_SetPointSrv(std::string, ros::NodeHandle&);
    ~ROSUnit_SetPointSrv();
    void receive_msg_data(DataMessage* t_msg){};

private:
    ros::ServiceServer m_server;

    static int internal_counter;
    static ROSUnit_SetPointSrv* m_ptr[ROSUnit_capacity];
    //Change the srv_callback code to reflect your system
    static bool(*callbackFunctionPointer[ROSUnit_capacity])(common_srv::set_point::Request&, common_srv::set_point::Response&);
    static bool srv_callback1(common_srv::set_point::Request&, common_srv::set_point::Response&);//TODO refactor through templates
    static bool srv_callback2(common_srv::set_point::Request&, common_srv::set_point::Response&);
    static bool srv_callback3(common_srv::set_point::Request&, common_srv::set_point::Response&);
    static bool srv_callback4(common_srv::set_point::Request&, common_srv::set_point::Response&);
    static bool srv_callback5(common_srv::set_point::Request&, common_srv::set_point::Response&);

};