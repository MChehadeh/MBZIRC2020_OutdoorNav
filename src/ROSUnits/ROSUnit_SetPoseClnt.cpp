#include "ROSUnit_SetPoseClnt.hpp"

ROSUnit_SetPoseClnt::ROSUnit_SetPoseClnt(std::string t_name, ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler)
{
    m_client = t_main_handler.serviceClient<common_srv::set_pose>(t_name);
}

ROSUnit_SetPoseClnt::~ROSUnit_SetPoseClnt()
{

}

void ROSUnit_SetPoseClnt::receive_msg_data(DataMessage* t_msg)
{
    //Change the below code to match your received msg
    if(t_msg->getType() == msg_type::POSE)
    {
        common_srv::set_pose t_srv;
        PoseMsg* t_poses = (PoseMsg*) t_msg;
        t_srv.request.pose.point.x = t_poses->pose.x;
        t_srv.request.pose.point.y = t_poses->pose.y;
        t_srv.request.pose.point.z = t_poses->pose.z;
        t_srv.request.pose.yaw.data = t_poses->pose.yaw;
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

