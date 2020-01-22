#include "Vector3DMessage.hpp"

Vector3DMessage::Vector3DMessage() {
}

Vector3DMessage::~Vector3DMessage() {

}

msg_type Vector3DMessage::getType(){
    return _type;
}

const int Vector3DMessage::getSize()
{
    return sizeof(this);
}

Vector3D<float> Vector3DMessage::getData(){
    return _data;
}

void Vector3DMessage::setVector3DMessage(Vector3D<float> t_data) {
    _type = msg_type::VECTOR3D;
    _data = t_data;
}
