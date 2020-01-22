#include "ROSUnit_SetPointSrv.hpp"

ROSUnit_SetPointSrv* ROSUnit_SetPointSrv::m_ptr[ROSUnit_capacity];
int ROSUnit_SetPointSrv::internal_counter=0;

bool(*ROSUnit_SetPointSrv::callbackFunctionPointer[ROSUnit_capacity])(common_srv::set_point::Request&, common_srv::set_point::Response&){
  ROSUnit_SetPointSrv::srv_callback1,
  ROSUnit_SetPointSrv::srv_callback2,
  ROSUnit_SetPointSrv::srv_callback3,
  ROSUnit_SetPointSrv::srv_callback4,
  ROSUnit_SetPointSrv::srv_callback5
};


ROSUnit_SetPointSrv::ROSUnit_SetPointSrv(std::string t_name, ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler)
{
    m_server = t_main_handler.advertiseService(t_name, ROSUnit_SetPointSrv::callbackFunctionPointer[internal_counter]);
    m_ptr[internal_counter] = this;
    internal_counter++;
}

ROSUnit_SetPointSrv::~ROSUnit_SetPointSrv()
{

}

bool ROSUnit_SetPointSrv::srv_callback1(common_srv::set_point::Request& req, common_srv::set_point::Response& res)
{
    //Change the code below to reflect your system
    Vector3DMessage t_msg;
    Vector3D<float> t_vec;
    t_vec.x = req.p.x;
    t_vec.y = req.p.y;
    t_vec.z = req.p.z;
    t_msg.setVector3DMessage(t_vec);
    m_ptr[0]->emit_message((DataMessage*) &t_msg);
    return true;
}

bool ROSUnit_SetPointSrv::srv_callback2(common_srv::set_point::Request& req, common_srv::set_point::Response& res)
{
    //Change the code below to reflect your system
    Vector3DMessage t_msg;
    Vector3D<float> t_vec;
    t_vec.x = req.p.x;
    t_vec.y = req.p.y;
    t_vec.z = req.p.z;
    t_msg.setVector3DMessage(t_vec);
    m_ptr[1]->emit_message((DataMessage*) &t_msg);
    return true;
}

bool ROSUnit_SetPointSrv::srv_callback3(common_srv::set_point::Request& req, common_srv::set_point::Response& res)
{
    //Change the code below to reflect your system
    Vector3DMessage t_msg;
    Vector3D<float> t_vec;
    t_vec.x = req.p.x;
    t_vec.y = req.p.y;
    t_vec.z = req.p.z;
    t_msg.setVector3DMessage(t_vec);
    m_ptr[2]->emit_message((DataMessage*) &t_msg);
    return true;
}

bool ROSUnit_SetPointSrv::srv_callback4(common_srv::set_point::Request& req, common_srv::set_point::Response& res)
{
    //Change the code below to reflect your system
    Vector3DMessage t_msg;
    Vector3D<float> t_vec;
    t_vec.x = req.p.x;
    t_vec.y = req.p.y;
    t_vec.z = req.p.z;
    t_msg.setVector3DMessage(t_vec);
    m_ptr[3]->emit_message((DataMessage*) &t_msg);
    return true;
}

bool ROSUnit_SetPointSrv::srv_callback5(common_srv::set_point::Request& req, common_srv::set_point::Response& res)
{
    //Change the code below to reflect your system
    Vector3DMessage t_msg;
    Vector3D<float> t_vec;
    t_vec.x = req.p.x;
    t_vec.y = req.p.y;
    t_vec.z = req.p.z;
    t_msg.setVector3DMessage(t_vec);
    m_ptr[4]->emit_message((DataMessage*) &t_msg);
    return true;
}