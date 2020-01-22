#include "ROSUnit_SetPosesClnt.hpp"

ROSUnit_SetPosesClnt::ROSUnit_SetPosesClnt(std::string t_name, ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler)
{
    m_client = t_main_handler.serviceClient<common_srv::set_poses>(t_name);
}

ROSUnit_SetPosesClnt::~ROSUnit_SetPosesClnt()
{

}

void ROSUnit_SetPosesClnt::receive_msg_data(DataMessage* t_msg)
{
    //Change the below code to match your received msg
    if(t_msg->getType() == msg_type::POSES)
    {
        common_srv::set_poses t_srv;
        PosesMsg* t_poses = (PosesMsg*) t_msg;
        for(int i = 0; i <= t_poses->p.poses.size(); i++)
        {
            common_srv::Pose t_pose;
            t_pose.point.x = t_poses->p.poses.at(i).x;
            t_pose.point.y = t_poses->p.poses.at(i).y;
            t_pose.point.z = t_poses->p.poses.at(i).z;
            t_pose.yaw.data = t_poses->p.poses.at(i).yaw;
            t_srv.request.poses.pose.push_back(t_pose);
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

