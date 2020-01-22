#include "ROSUnit_SetVectorSrv.hpp"

ROSUnit_SetVectorSrv* ROSUnit_SetVectorSrv::m_ptr[ROSUnit_capacity];
int ROSUnit_SetVectorSrv::internal_counter=0;


bool(*ROSUnit_SetVectorSrv::callbackFunctionPointer[ROSUnit_capacity])(common_srv::set_vector::Request&, common_srv::set_vector::Response&){
  ROSUnit_SetVectorSrv::srv_callback1,
  ROSUnit_SetVectorSrv::srv_callback2,
  ROSUnit_SetVectorSrv::srv_callback3,
  ROSUnit_SetVectorSrv::srv_callback4,
  ROSUnit_SetVectorSrv::srv_callback5
};

ROSUnit_SetVectorSrv::ROSUnit_SetVectorSrv(std::string t_name, ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler)
{
    m_server = t_main_handler.advertiseService(t_name, ROSUnit_SetVectorSrv::callbackFunctionPointer[internal_counter]);
    m_ptr[internal_counter] = this;
    internal_counter++;
}

ROSUnit_SetVectorSrv::~ROSUnit_SetVectorSrv()
{

}

bool ROSUnit_SetVectorSrv::srv_callback1(common_srv::set_vector::Request& req, common_srv::set_vector::Response& res)
{
    //Change the code below to reflect your system
    VectorMsg t_msg;
    t_msg.p1.x = req.p1.x;
    t_msg.p1.y = req.p1.y;
    t_msg.p1.z = req.p1.z;
    t_msg.p2.x = req.p2.x;
    t_msg.p2.y = req.p2.y;
    t_msg.p2.z = req.p2.z;
    m_ptr[0]->emit_message((DataMessage*) &t_msg);
    return true;
}

bool ROSUnit_SetVectorSrv::srv_callback2(common_srv::set_vector::Request& req, common_srv::set_vector::Response& res)
{
    //Change the code below to reflect your system
    VectorMsg t_msg;
    t_msg.p1.x = req.p1.x;
    t_msg.p1.y = req.p1.y;
    t_msg.p1.z = req.p1.z;
    t_msg.p2.x = req.p2.x;
    t_msg.p2.y = req.p2.y;
    t_msg.p2.z = req.p2.z;
    m_ptr[1]->emit_message((DataMessage*) &t_msg);
    return true;
}

bool ROSUnit_SetVectorSrv::srv_callback3(common_srv::set_vector::Request& req, common_srv::set_vector::Response& res)
{
    //Change the code below to reflect your system
    VectorMsg t_msg;
    t_msg.p1.x = req.p1.x;
    t_msg.p1.y = req.p1.y;
    t_msg.p1.z = req.p1.z;
    t_msg.p2.x = req.p2.x;
    t_msg.p2.y = req.p2.y;
    t_msg.p2.z = req.p2.z;
    m_ptr[2]->emit_message((DataMessage*) &t_msg);
    return true;
}

bool ROSUnit_SetVectorSrv::srv_callback4(common_srv::set_vector::Request& req, common_srv::set_vector::Response& res)
{
    //Change the code below to reflect your system
    VectorMsg t_msg;
    t_msg.p1.x = req.p1.x;
    t_msg.p1.y = req.p1.y;
    t_msg.p1.z = req.p1.z;
    t_msg.p2.x = req.p2.x;
    t_msg.p2.y = req.p2.y;
    t_msg.p2.z = req.p2.z;
    m_ptr[3]->emit_message((DataMessage*) &t_msg);
    return true;
}

bool ROSUnit_SetVectorSrv::srv_callback5(common_srv::set_vector::Request& req, common_srv::set_vector::Response& res)
{
    //Change the code below to reflect your system
    VectorMsg t_msg;
    t_msg.p1.x = req.p1.x;
    t_msg.p1.y = req.p1.y;
    t_msg.p1.z = req.p1.z;
    t_msg.p2.x = req.p2.x;
    t_msg.p2.y = req.p2.y;
    t_msg.p2.z = req.p2.z;
    m_ptr[4]->emit_message((DataMessage*) &t_msg);
    return true;
}