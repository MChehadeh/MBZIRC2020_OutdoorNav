#include "AttitudeMsg.hpp"

msg_type AttitudeMsg::getType()
{
	return msg_type::ATTITUDE;
}

const int AttitudeMsg::getSize()
{
	return sizeof(AttitudeMsg);
}