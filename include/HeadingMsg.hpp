#pragma once 

#include "DataMessage.hpp"
#include "common_types.hpp"

class HeadingMsg : public DataMessage
{
public:

	msg_type getType();
	const int getSize();

	float yaw=0;	 
};