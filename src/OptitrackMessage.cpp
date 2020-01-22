#include "OptitrackMessage.hpp"

OptitrackMessage::OptitrackMessage(Vector3D<float> t_position, Quaternion t_att_head) {

    _attitude_heading = t_att_head;
    _position = t_position;
    _type = msg_type::optitrack;
}

OptitrackMessage::OptitrackMessage() {
}

OptitrackMessage::~OptitrackMessage() {

}

msg_type OptitrackMessage::getType(){
    return _type;
}

double OptitrackMessage::getTime(){
    return _time;
}

const int OptitrackMessage::getSize()
{
    return sizeof(this);
}
    
Vector3D<float> OptitrackMessage::getPosition(){
    return _position;
}

Quaternion OptitrackMessage::getAttitudeHeading(){
    return _attitude_heading;
}

void OptitrackMessage::setOptitrackMessage(Vector3D<float> t_position, Quaternion t_att_head, double t_time) {

    _attitude_heading = t_att_head;
    _position = t_position;
    _time = t_time;
    _type = msg_type::optitrack;
}