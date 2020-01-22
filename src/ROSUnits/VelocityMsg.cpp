#include "VelocityMsg.hpp"

msg_type VelocityMsg::getType()
{
	return msg_type::VELOCITY;
}

const int VelocityMsg::getSize()
{
	return sizeof(VelocityMsg);
}