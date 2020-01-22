#include "ROSUnit_SetPointsClnt.hpp"

ROSUnit_SetPointsClnt::ROSUnit_SetPointsClnt(std::string t_name, ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler)
{
    m_client = t_main_handler.serviceClient<common_srv::set_points>(t_name);
}

ROSUnit_SetPointsClnt::~ROSUnit_SetPointsClnt()
{

}

void ROSUnit_SetPointsClnt::receive_msg_data(DataMessage* t_msg)
{
    //Change the below code to match your received msg
    if(t_msg->getType() == msg_type::POINTS)
    {
        common_srv::set_points t_srv;
        PointsMsg* t_points = (PointsMsg*) t_msg;
        for(int i = 0; i < t_points->points.size(); i++)
        {
            geometry_msgs::Point t_point;
            t_point.x =  t_points->points.at(i).x;
            t_point.y =  t_points->points.at(i).y;
            t_point.z =  t_points->points.at(i).z;
            t_srv.request.p.push_back(t_point);
        }
        if(m_client.call(t_srv))
        {
            //TODO: add success condition
        }
        else
        {
            //TODO: add error
        }
        
    }
}

