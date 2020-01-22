#include "ROSUnit_SetVectorClnt.hpp"

ROSUnit_SetVectorClnt::ROSUnit_SetVectorClnt(std::string t_name, ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler)
{
    m_client = t_main_handler.serviceClient<common_srv::set_vector>(t_name);
}

ROSUnit_SetVectorClnt::~ROSUnit_SetVectorClnt()
{

}

void ROSUnit_SetVectorClnt::receive_msg_data(DataMessage* t_msg)
{
    //Change the below code to match your received msg
    if(t_msg->getType() == msg_type::VECTOR)
    {
        common_srv::set_vector t_srv;
        VectorMsg* t_vector = (VectorMsg*) t_msg;
        t_srv.request.p1.x = t_vector->p1.x;
        t_srv.request.p1.y = t_vector->p1.y;
        t_srv.request.p1.z = t_vector->p1.z;
        t_srv.request.p1.x = t_vector->p2.x;
        t_srv.request.p1.y = t_vector->p2.y;
        t_srv.request.p1.z = t_vector->p2.z;
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

