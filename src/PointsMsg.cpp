#include "PointsMsg.hpp"

PointsMsg::PointsMsg()
{

}

PointsMsg::~PointsMsg()
{

}

msg_type PointsMsg::getType()
{
    return msg_type::POINTS;
}

const int PointsMsg::getSize()
{
    return sizeof(*this);
}