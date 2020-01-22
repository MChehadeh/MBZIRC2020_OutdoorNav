#include "FloatMsg.hpp"

FloatMsg::FloatMsg()
{
}

FloatMsg::~FloatMsg()
{

}

msg_type FloatMsg::getType()
{
    return msg_type::FLOAT;
}

const int FloatMsg::getSize()
{
    return sizeof(FloatMsg);
}