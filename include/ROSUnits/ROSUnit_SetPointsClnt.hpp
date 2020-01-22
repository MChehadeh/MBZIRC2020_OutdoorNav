#pragma once

#include "ROSUnit.hpp"
#include "geometry_msgs/Point.h"
#include "common_srv/set_points.h"
//Change the msg type code to reflect your system
#include "PointsMsg.hpp"

class ROSUnit_SetPointsClnt : public ROSUnit
{
    public:

        ROSUnit_SetPointsClnt(std::string, ros::NodeHandle&);
        ~ROSUnit_SetPointsClnt();
        //Change the receive_msg_data code to reflect your system
        void receive_msg_data(DataMessage* t_msg);

    private:

        ros::ServiceClient m_client;
};