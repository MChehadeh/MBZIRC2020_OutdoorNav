#include "PositionMsg.hpp"

msg_type PositionMsg::getType()
{
	return msg_type::POSITION;
}

const int PositionMsg::getSize()
{
	return sizeof(PositionMsg);
}