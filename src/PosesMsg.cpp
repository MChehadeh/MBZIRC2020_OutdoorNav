#include "PosesMsg.hpp"

PosesMsg::PosesMsg()
{

}

PosesMsg::~PosesMsg()
{

}

msg_type PosesMsg::getType()
{
    return msg_type::POSES;
}

const int PosesMsg::getSize()
{
    return sizeof(*this);
}