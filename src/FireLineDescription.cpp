#include "FireLineDescription.hpp"

FireLineDescription::FireLineDescription() {

}

FireLineDescription::~FireLineDescription() {

}

msg_type FireLineDescription::getType()
{
    return msg_type::FIRE_LINE_DESC;
}

const int FireLineDescription::getSize()
{
    return sizeof(FireLineDescription);
}

void FireLineDescription::setFireLineMessage(Vector3D<float> t_point1, Vector3D<float> t_point2)
{
    point1 = t_point1;
    point2 = t_point2;
}