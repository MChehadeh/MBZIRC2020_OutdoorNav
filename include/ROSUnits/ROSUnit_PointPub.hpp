#pragma once

#include "ROSUnit.hpp"
#include "geometry_msgs/Point.h"
//Change the msg type to match your received msg
#include "Vector3DMessage.hpp"

class ROSUnit_PointPub : public ROSUnit
{
    public:

        ROSUnit_PointPub(std::string, ros::NodeHandle&);
        ~ROSUnit_PointPub();
        //Change the receive_msg_data code to reflect your system
        void receive_msg_data(DataMessage* t_msg);

    private:

        ros::Publisher m_pub;
};