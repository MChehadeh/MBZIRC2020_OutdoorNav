#pragma once 


#include "DataMessage.hpp"
#include "common_types.hpp"

class AttitudeMsg : public DataMessage
{
public:

	msg_type getType();
	const int getSize();

	float pitch=0, roll=0;
};