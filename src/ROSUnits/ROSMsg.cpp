#include "ROSMsg.hpp"

ROSMsg::ROSMsg() {
    _type = msg_type::ROS;
}

ROSMsg::~ROSMsg() {

}

msg_type ROSMsg::getType(){
    return _type;
}
ros_msg_type ROSMsg::getROSMsgType(){
    return _ros_type;
}
const int ROSMsg::getSize(){
    return sizeof(this);
}
void ROSMsg::setPosition(Vector3D<float> tmp){
    _ros_type = ros_msg_type::POSITION;
    _position = tmp;
}
void ROSMsg::setOrientation(Vector3D<float> tmp){
    _ros_type = ros_msg_type::ORIENTATION;
    _orientation = tmp;
}
void ROSMsg::setX_PV(Vector3D<float> tmp){
    _ros_type = ros_msg_type::X_PV;
    _x_pv = tmp;
}
void ROSMsg::setY_PV(Vector3D<float> tmp){
    _ros_type = ros_msg_type::Y_PV;
    _y_pv = tmp;
}
void ROSMsg::setZ_PV(Vector3D<float> tmp){
    _ros_type = ros_msg_type::Z_PV;
    _z_pv = tmp;
}
void ROSMsg::setRoll_PV(Vector3D<float> tmp){
    _ros_type = ros_msg_type::ROLL_PV;
    _roll_pv = tmp;
}
void ROSMsg::setPitch_PV(Vector3D<float> tmp){
    _ros_type = ros_msg_type::PITCH_PV;
    _pitch_pv = tmp;
}
void ROSMsg::setYaw_PV(Vector3D<float> tmp){
    _ros_type = ros_msg_type::YAW_PV;
    _yaw_pv = tmp;
}
void ROSMsg::setControlSystem(float tmp){
    _ros_type = ros_msg_type::CONTROLSYSTEM;
    _control_system = tmp;
}
void ROSMsg::setActuation(float* tmp){
    _ros_type = ros_msg_type::ACTUATION;
    _actuation = tmp;
}
Vector3D<float> ROSMsg::getPosition(){
    return _position;
}