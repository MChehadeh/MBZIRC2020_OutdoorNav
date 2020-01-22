#pragma once

#include "ROSUnit.hpp"
#include "common_srv/Pose.h"
#include "common_srv/set_poses.h"
//Change the msg type code to reflect your system
#include "PosesMsg.hpp"

class ROSUnit_SetPosesClnt : public ROSUnit
{
    public:

        ROSUnit_SetPosesClnt(std::string, ros::NodeHandle&);
        ~ROSUnit_SetPosesClnt();
        //Change the receive_msg_data code to reflect your system
        void receive_msg_data(DataMessage* t_msg);

    private:

        ros::ServiceClient m_client;
};