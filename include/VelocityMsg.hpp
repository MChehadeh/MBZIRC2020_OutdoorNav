#pragma once 

#include "DataMessage.hpp"
#include "common_types.hpp"

class VelocityMsg : public DataMessage
{
public:

	msg_type getType();
	const int getSize();

	float dx, dy, dz;	
};