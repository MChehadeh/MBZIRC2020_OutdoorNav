#include "EmptyMsg.hpp"

EmptyMsg::EmptyMsg()
{
}

EmptyMsg::~EmptyMsg()
{

}

msg_type EmptyMsg::getType()
{
    return msg_type::EMPTY;
}

const int EmptyMsg::getSize()
{
    return sizeof(EmptyMsg);
}