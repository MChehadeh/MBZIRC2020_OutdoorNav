#pragma once
#include "DataMessage.hpp"
#include "Vector3D.hpp"

class ROSMsg : public DataMessage {

private:
    msg_type _type;
    ros_msg_type _ros_type;
    Vector3D<float> _position;
    Vector3D<float> _orientation;
    Vector3D<float> _x_pv;
    Vector3D<float> _y_pv;
    Vector3D<float> _z_pv;
    Vector3D<float> _roll_pv;
    Vector3D<float> _pitch_pv;
    Vector3D<float> _yaw_pv;
    float _control_system;
    float* _actuation;

public:
    msg_type getType();
    ros_msg_type getROSMsgType();
    const int getSize();
    void setPosition(Vector3D<float>);
    void setOrientation(Vector3D<float>);
    void setX_PV(Vector3D<float>);
    void setY_PV(Vector3D<float>);
    void setZ_PV(Vector3D<float>);
    void setRoll_PV(Vector3D<float>);
    void setPitch_PV(Vector3D<float>);
    void setYaw_PV(Vector3D<float>);
    void setControlSystem(float);
    void setActuation(float*);
    Vector3D<float> getPosition();

    ROSMsg();
    ~ROSMsg();
};