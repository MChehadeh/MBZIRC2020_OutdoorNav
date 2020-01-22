#pragma once 

#include "DataMessage.hpp"
#include "common_types.hpp"
#include "Waypoint.hpp"
class WaypointMsg : public DataMessage
{
public:

	msg_type getType();
	const int getSize();

	Waypoint waypoint;	//TODO: This should use Vector3D
};