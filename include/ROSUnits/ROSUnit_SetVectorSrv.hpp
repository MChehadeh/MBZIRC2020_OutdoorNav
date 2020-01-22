#pragma once

#include "ROSUnit.hpp"
#include "common_srv/set_vector.h"
//Change the msg type to match your received msg
#include "VectorMsg.hpp"

class ROSUnit_SetVectorSrv : public ROSUnit
{
public:

    ROSUnit_SetVectorSrv(std::string, ros::NodeHandle&);
    ~ROSUnit_SetVectorSrv();
    void receive_msg_data(DataMessage* t_msg) {};

private:

    ros::ServiceServer m_server;

    static int internal_counter;
    static ROSUnit_SetVectorSrv* m_ptr[ROSUnit_capacity];
    //Change the srv_callback code to reflect your system
    static bool(*callbackFunctionPointer[ROSUnit_capacity])(common_srv::set_vector::Request&, common_srv::set_vector::Response&);
    static bool srv_callback1(common_srv::set_vector::Request&, common_srv::set_vector::Response&);//TODO refactor through templates
    static bool srv_callback2(common_srv::set_vector::Request&, common_srv::set_vector::Response&);
    static bool srv_callback3(common_srv::set_vector::Request&, common_srv::set_vector::Response&);
    static bool srv_callback4(common_srv::set_vector::Request&, common_srv::set_vector::Response&);
    static bool srv_callback5(common_srv::set_vector::Request&, common_srv::set_vector::Response&);


};