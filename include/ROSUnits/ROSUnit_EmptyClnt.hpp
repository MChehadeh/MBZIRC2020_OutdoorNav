#pragma once

#include "ROSUnit.hpp"
#include "std_srvs/Empty.h"
//Change the msg type to match your received msg
#include "EmptyMsg.hpp"

class ROSUnit_EmptyClnt : public ROSUnit
{
    public:
    
        ROSUnit_EmptyClnt(std::string, ros::NodeHandle&);
        ~ROSUnit_EmptyClnt();
        //Change the receive_msg_data code to reflect your system
        void receive_msg_data(DataMessage* t_msg);

    private:

        ros::ServiceClient m_client;
};