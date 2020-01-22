#include "IntegerMsg.hpp"

IntegerMsg::IntegerMsg()
{
}

IntegerMsg::~IntegerMsg()
{

}

msg_type IntegerMsg::getType()
{
    return msg_type::INTEGER;
}

const int IntegerMsg::getSize()
{
    return sizeof(IntegerMsg);
}