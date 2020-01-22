#include "ROSUnit_PointPub.hpp"

ROSUnit_PointPub::ROSUnit_PointPub(std::string t_name, ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler)
{
    m_pub = t_main_handler.advertise<geometry_msgs::Point>(t_name, 1, true);
}

ROSUnit_PointPub::~ROSUnit_PointPub()
{

}

void ROSUnit_PointPub::receive_msg_data(DataMessage* t_msg)
{
    //Change the below code to match your received msg
    if(t_msg->getType() == msg_type::VECTOR3D)
    {
        Vector3DMessage* t_vec = (Vector3DMessage*) t_msg;
        geometry_msgs::Point t_point;
        t_point.x = t_vec->getData().x;
        t_point.y = t_vec->getData().y;
        t_point.z = t_vec->getData().z;
        m_pub.publish(t_point);
    }
}