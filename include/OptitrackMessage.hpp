#pragma once
#include "DataMessage.hpp"
#include "Vector3D.hpp"
#include "Quaternion.hpp"

class OptitrackMessage : public DataMessage{

private:
    Vector3D<float> _position;
    double _time;
    Quaternion _attitude_heading; 
    msg_type _type;

public:

    msg_type getType();
    const int getSize();
    double getTime();
    Vector3D<float> getPosition();
    Quaternion getAttitudeHeading();
    void setOptitrackMessage(Vector3D<float>, Quaternion, double);

    OptitrackMessage(Vector3D<float>, Quaternion);
    OptitrackMessage();
    ~OptitrackMessage();
};