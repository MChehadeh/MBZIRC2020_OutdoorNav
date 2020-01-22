#include "ROSUnit_SetFloatClnt.hpp"

ROSUnit_SetFloatClnt::ROSUnit_SetFloatClnt(std::string t_name, ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler)
{
    m_client = t_main_handler.serviceClient<common_srv::set_float>(t_name);
}

ROSUnit_SetFloatClnt::~ROSUnit_SetFloatClnt()
{

}

void ROSUnit_SetFloatClnt::receive_msg_data(DataMessage* t_msg)
{
    //Change the below code to match your received msg
    if(t_msg->getType() == msg_type::FLOAT)
    {
        common_srv::set_float t_srv;
        t_srv.request.data = ((FloatMsg*) t_msg)->data;
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