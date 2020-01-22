#include "Vector2DMsg.hpp"

Vector2DMsg::Vector2DMsg() {
}

Vector2DMsg::~Vector2DMsg() {

}

msg_type Vector2DMsg::getType(){
    return msg_type::VECTOR2D;
}

const int Vector2DMsg::getSize()
{
    return sizeof(*this);
}