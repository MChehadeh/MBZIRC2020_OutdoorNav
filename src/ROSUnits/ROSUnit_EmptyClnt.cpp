#include "ROSUnit_EmptyClnt.hpp"

ROSUnit_EmptyClnt::ROSUnit_EmptyClnt(std::string t_name, ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler)
{
    m_client = t_main_handler.serviceClient<std_srvs::Empty>(t_name);
}

ROSUnit_EmptyClnt::~ROSUnit_EmptyClnt()
{

}

void ROSUnit_EmptyClnt::receive_msg_data(DataMessage* t_msg)
{
    //Change the below code to match your received msg
    if(t_msg->getType() == msg_type::EMPTY)
    {
        std_srvs::Empty t_srv;
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