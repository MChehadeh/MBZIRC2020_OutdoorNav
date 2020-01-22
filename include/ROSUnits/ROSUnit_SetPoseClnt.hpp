#pragma once

#include "ROSUnit.hpp"
#include "common_srv/set_pose.h"
//Change the msg type code to reflect your system
#include "PoseMsg.hpp"

class ROSUnit_SetPoseClnt : public ROSUnit
{
    public:

        ROSUnit_SetPoseClnt(std::string, ros::NodeHandle&);
        ~ROSUnit_SetPoseClnt();
        //Change the receive_msg_data code to reflect your system
        void receive_msg_data(DataMessage* t_msg);

    private:

        ros::ServiceClient m_client;
};