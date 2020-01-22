#include "VectorMsg.hpp"

VectorMsg::VectorMsg()
{

}

VectorMsg::~VectorMsg()
{

}

msg_type VectorMsg::getType()
{
    return msg_type::VECTOR;
}

const int VectorMsg::getSize()
{
    return sizeof(VectorMsg);
}