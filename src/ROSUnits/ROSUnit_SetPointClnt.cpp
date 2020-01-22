#include "ROSUnit_SetPointClnt.hpp"

ROSUnit_SetPointClnt::ROSUnit_SetPointClnt(std::string t_name, ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler)
{
    m_client = t_main_handler.serviceClient<common_srv::set_point>(t_name);
}

ROSUnit_SetPointClnt::~ROSUnit_SetPointClnt()
{

}

void ROSUnit_SetPointClnt::receive_msg_data(DataMessage* t_msg)
{
    //Change the below code to match your received msg
    if(t_msg->getType() == msg_type::VECTOR3D)
    {
        common_srv::set_point t_srv;
        Vector3DMessage* t_vector = (Vector3DMessage*) t_msg;
        t_srv.request.p.x = t_vector->getData().x;
        t_srv.request.p.y = t_vector->getData().y;
        t_srv.request.p.z = t_vector->getData().z;
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

