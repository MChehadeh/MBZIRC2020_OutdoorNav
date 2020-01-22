#include "filterPointMsg.hpp"

filterPointMsg::filterPointMsg() {
}

filterPointMsg::~filterPointMsg() {
}

msg_type filterPointMsg::getType()
{
    return msg_type::FILTER_POINT;
}

const int filterPointMsg::getSize()
{
    return sizeof(filterPointMsg);
}

void filterPointMsg::setFilterMessage(Vector3D<float> t_point)
{
    filterPoint = t_point;
}