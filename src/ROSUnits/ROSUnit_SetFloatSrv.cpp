#include "ROSUnit_SetFloatSrv.hpp"

ROSUnit_SetFloatSrv* ROSUnit_SetFloatSrv::m_ptr[ROSUnit_capacity];
int ROSUnit_SetFloatSrv::internal_counter=0;

bool(*ROSUnit_SetFloatSrv::callbackFunctionPointer[ROSUnit_capacity])(common_srv::set_float::Request&, common_srv::set_float::Response&){
  ROSUnit_SetFloatSrv::srv_callback1,
  ROSUnit_SetFloatSrv::srv_callback2,
  ROSUnit_SetFloatSrv::srv_callback3,
  ROSUnit_SetFloatSrv::srv_callback4,
  ROSUnit_SetFloatSrv::srv_callback5
};

ROSUnit_SetFloatSrv::ROSUnit_SetFloatSrv(std::string t_name, ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler)
{
    m_server = t_main_handler.advertiseService(t_name, ROSUnit_SetFloatSrv::callbackFunctionPointer[internal_counter]);
    m_ptr[internal_counter] = this;
    internal_counter++;
}

ROSUnit_SetFloatSrv::~ROSUnit_SetFloatSrv()
{

}

bool ROSUnit_SetFloatSrv::srv_callback1(common_srv::set_float::Request& req, common_srv::set_float::Response& res)
{
    //Change the code below to reflect your system
    FloatMsg t_msg;
    t_msg.data = req.data;
    m_ptr[0]->emit_message((DataMessage*) &t_msg);
    return true;
}
bool ROSUnit_SetFloatSrv::srv_callback2(common_srv::set_float::Request& req, common_srv::set_float::Response& res)
{
    //Change the code below to reflect your system
    FloatMsg t_msg;
    t_msg.data = req.data;
    m_ptr[1]->emit_message((DataMessage*) &t_msg);
    return true;
}
bool ROSUnit_SetFloatSrv::srv_callback3(common_srv::set_float::Request& req, common_srv::set_float::Response& res)
{
    //Change the code below to reflect your system
    FloatMsg t_msg;
    t_msg.data = req.data;
    m_ptr[2]->emit_message((DataMessage*) &t_msg);
    return true;
}
bool ROSUnit_SetFloatSrv::srv_callback4(common_srv::set_float::Request& req, common_srv::set_float::Response& res)
{
    //Change the code below to reflect your system
    FloatMsg t_msg;
    t_msg.data = req.data;
    m_ptr[3]->emit_message((DataMessage*) &t_msg);
    return true;
}
bool ROSUnit_SetFloatSrv::srv_callback5(common_srv::set_float::Request& req, common_srv::set_float::Response& res)
{
    //Change the code below to reflect your system
    FloatMsg t_msg;
    t_msg.data = req.data;
    m_ptr[4]->emit_message((DataMessage*) &t_msg);
    return true;
}