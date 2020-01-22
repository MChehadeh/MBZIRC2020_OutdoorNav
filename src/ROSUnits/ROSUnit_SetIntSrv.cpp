#include "ROSUnit_SetIntSrv.hpp"

ROSUnit_SetIntSrv* ROSUnit_SetIntSrv::m_ptr[ROSUnit_capacity];
int ROSUnit_SetIntSrv::internal_counter=0;

bool(*ROSUnit_SetIntSrv::callbackFunctionPointer[ROSUnit_capacity])(common_srv::set_int::Request&, common_srv::set_int::Response&){
  ROSUnit_SetIntSrv::srv_callback1,
  ROSUnit_SetIntSrv::srv_callback2,
  ROSUnit_SetIntSrv::srv_callback3,
  ROSUnit_SetIntSrv::srv_callback4,
  ROSUnit_SetIntSrv::srv_callback5
};

ROSUnit_SetIntSrv::ROSUnit_SetIntSrv(std::string t_name, ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler)
{
    m_server = t_main_handler.advertiseService(t_name, ROSUnit_SetIntSrv::callbackFunctionPointer[internal_counter]);
    m_ptr[internal_counter] = this;
    internal_counter++;
}

ROSUnit_SetIntSrv::~ROSUnit_SetIntSrv()
{

}

bool ROSUnit_SetIntSrv::srv_callback1(common_srv::set_int::Request& req, common_srv::set_int::Response& res)
{
    //Change the code below to reflect your system
    IntegerMsg t_msg;
    t_msg.data = req.data;
    m_ptr[0]->emit_message((DataMessage*) &t_msg);
    return true;
}

bool ROSUnit_SetIntSrv::srv_callback2(common_srv::set_int::Request& req, common_srv::set_int::Response& res)
{
    //Change the code below to reflect your system
    IntegerMsg t_msg;
    t_msg.data = req.data;
    m_ptr[1]->emit_message((DataMessage*) &t_msg);
    return true;
}

bool ROSUnit_SetIntSrv::srv_callback3(common_srv::set_int::Request& req, common_srv::set_int::Response& res)
{
    //Change the code below to reflect your system
    IntegerMsg t_msg;
    t_msg.data = req.data;
    m_ptr[2]->emit_message((DataMessage*) &t_msg);
    return true;
}

bool ROSUnit_SetIntSrv::srv_callback4(common_srv::set_int::Request& req, common_srv::set_int::Response& res)
{
    //Change the code below to reflect your system
    IntegerMsg t_msg;
    t_msg.data = req.data;
    m_ptr[3]->emit_message((DataMessage*) &t_msg);
    return true;
}

bool ROSUnit_SetIntSrv::srv_callback5(common_srv::set_int::Request& req, common_srv::set_int::Response& res)
{
    //Change the code below to reflect your system
    IntegerMsg t_msg;
    t_msg.data = req.data;
    m_ptr[4]->emit_message((DataMessage*) &t_msg);
    return true;
}