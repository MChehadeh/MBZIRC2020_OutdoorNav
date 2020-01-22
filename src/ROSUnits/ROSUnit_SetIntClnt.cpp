#include "ROSUnit_SetIntClnt.hpp"

ROSUnit_SetIntClnt::ROSUnit_SetIntClnt(std::string t_name, ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler)
{
    m_client = t_main_handler.serviceClient<common_srv::set_int>(t_name);
}

ROSUnit_SetIntClnt::~ROSUnit_SetIntClnt()
{

}

void ROSUnit_SetIntClnt::receive_msg_data(DataMessage* t_msg)
{
    //Change the below code to match your received msg
    if(t_msg->getType() == msg_type::INTEGER)
    {
        common_srv::set_int t_srv;
        IntegerMsg* t_vector = (IntegerMsg*) t_msg;
        t_srv.request.data = t_vector->data;
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