#pragma once

#include "ROSUnit.hpp"
#include "common_srv/set_pose.h"
//Change the msg type to match your received msg
#include "PoseMsg.hpp"

class ROSUnit_SetPoseSrv : public ROSUnit
{
public:
    
    ROSUnit_SetPoseSrv(std::string, ros::NodeHandle&);
    ~ROSUnit_SetPoseSrv();
    void receive_msg_data(DataMessage* t_msg){};

private:

    ros::ServiceServer m_server;

    static int internal_counter;
    static ROSUnit_SetPoseSrv* m_ptr[ROSUnit_capacity];
    //Change the srv_callback code to reflect your system
    static bool(*callbackFunctionPointer[ROSUnit_capacity])(common_srv::set_pose::Request&, common_srv::set_pose::Response&);
    static bool srv_callback1(common_srv::set_pose::Request&, common_srv::set_pose::Response&);//TODO refactor through templates
    static bool srv_callback2(common_srv::set_pose::Request&, common_srv::set_pose::Response&);
    static bool srv_callback3(common_srv::set_pose::Request&, common_srv::set_pose::Response&);
    static bool srv_callback4(common_srv::set_pose::Request&, common_srv::set_pose::Response&);
    static bool srv_callback5(common_srv::set_pose::Request&, common_srv::set_pose::Response&);


};