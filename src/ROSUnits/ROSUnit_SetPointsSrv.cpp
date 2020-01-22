#include "ROSUnit_SetPointsSrv.hpp"

ROSUnit_SetPointsSrv* ROSUnit_SetPointsSrv::m_ptr[ROSUnit_capacity];
int ROSUnit_SetPointsSrv::internal_counter=0;

bool(*ROSUnit_SetPointsSrv::callbackFunctionPointer[ROSUnit_capacity])(common_srv::set_points::Request&, common_srv::set_points::Response&){
  ROSUnit_SetPointsSrv::srv_callback1,
  ROSUnit_SetPointsSrv::srv_callback2,
  ROSUnit_SetPointsSrv::srv_callback3,
  ROSUnit_SetPointsSrv::srv_callback4,
  ROSUnit_SetPointsSrv::srv_callback5
};


ROSUnit_SetPointsSrv::ROSUnit_SetPointsSrv(std::string t_name, ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler)
{
    m_server = t_main_handler.advertiseService(t_name, ROSUnit_SetPointsSrv::callbackFunctionPointer[internal_counter]);
    m_ptr[internal_counter] = this;
    internal_counter++;
}

ROSUnit_SetPointsSrv::~ROSUnit_SetPointsSrv()
{

}

bool ROSUnit_SetPointsSrv::srv_callback1(common_srv::set_points::Request& req, common_srv::set_points::Response& res)
{
    //Change the code below to reflect your system
    PointsMsg t_msg;
    for(int i = 0; i < req.p.size(); i++)
    {
        Vector3D<float> t_vec;
        t_vec.x = req.p.at(i).x;
        t_vec.y = req.p.at(i).y;
        t_vec.z = req.p.at(i).z;
        t_msg.points.push_back(t_vec);
    }
    m_ptr[0]->emit_message((DataMessage*) &t_msg);
    return true;
}

bool ROSUnit_SetPointsSrv::srv_callback2(common_srv::set_points::Request& req, common_srv::set_points::Response& res)
{
    //Change the code below to reflect your system
    PointsMsg t_msg;
    for(int i = 0; i < req.p.size(); i++)
    {
        Vector3D<float> t_vec;
        t_vec.x = req.p.at(i).x;
        t_vec.y = req.p.at(i).y;
        t_vec.z = req.p.at(i).z;
        t_msg.points.push_back(t_vec);
    }
    m_ptr[1]->emit_message((DataMessage*) &t_msg);
    return true;
}

bool ROSUnit_SetPointsSrv::srv_callback3(common_srv::set_points::Request& req, common_srv::set_points::Response& res)
{
    //Change the code below to reflect your system
    PointsMsg t_msg;
    for(int i = 0; i < req.p.size(); i++)
    {
        Vector3D<float> t_vec;
        t_vec.x = req.p.at(i).x;
        t_vec.y = req.p.at(i).y;
        t_vec.z = req.p.at(i).z;
        t_msg.points.push_back(t_vec);
    }
    m_ptr[2]->emit_message((DataMessage*) &t_msg);
    return true;
}

bool ROSUnit_SetPointsSrv::srv_callback4(common_srv::set_points::Request& req, common_srv::set_points::Response& res)
{
    //Change the code below to reflect your system
    PointsMsg t_msg;
    for(int i = 0; i < req.p.size(); i++)
    {
        Vector3D<float> t_vec;
        t_vec.x = req.p.at(i).x;
        t_vec.y = req.p.at(i).y;
        t_vec.z = req.p.at(i).z;
        t_msg.points.push_back(t_vec);
    }
    m_ptr[3]->emit_message((DataMessage*) &t_msg);
    return true;
}

bool ROSUnit_SetPointsSrv::srv_callback5(common_srv::set_points::Request& req, common_srv::set_points::Response& res)
{
    //Change the code below to reflect your system
    PointsMsg t_msg;
    for(int i = 0; i < req.p.size(); i++)
    {
        Vector3D<float> t_vec;
        t_vec.x = req.p.at(i).x;
        t_vec.y = req.p.at(i).y;
        t_vec.z = req.p.at(i).z;
        t_msg.points.push_back(t_vec);
    }
    m_ptr[4]->emit_message((DataMessage*) &t_msg);
    return true;
}
