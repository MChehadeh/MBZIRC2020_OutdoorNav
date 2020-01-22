#include "TaggedPosesMsg.hpp"

TaggedPosesMsg::TaggedPosesMsg()
{

}

TaggedPosesMsg::~TaggedPosesMsg()
{

}

msg_type TaggedPosesMsg::getType()
{
    return msg_type::TAGGEDPOSES;
}

const int TaggedPosesMsg::getSize()
{
    return sizeof(*this);
}