#include "WaypointMsg.hpp"
    msg_type WaypointMsg::getType(){
        return msg_type::waypoint;
    }
    const int WaypointMsg::getSize(){
        return sizeof(*this);
    }