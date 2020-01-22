#pragma once

#include "ROSUnit.hpp"
#include "common_srv/set_int.h"
//Change the msg type to match your received msg
#include "IntegerMsg.hpp"

class ROSUnit_SetIntClnt : public ROSUnit
{
    public:
    
        ROSUnit_SetIntClnt(std::string, ros::NodeHandle&);
        ~ROSUnit_SetIntClnt();
        //Change the receive_msg_data code to reflect your system
        void receive_msg_data(DataMessage* t_msg);

    private:

        ros::ServiceClient m_client;
};