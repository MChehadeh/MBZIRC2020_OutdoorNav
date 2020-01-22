#pragma once
#include "DataMessage.hpp"
#include "Vector3D.hpp"
#include "Quaternion.hpp"
#include "common_types.hpp"

class RTKMessageVelocity : public DataMessage{

public:
    Vector3D<double> velocity;
    int id; 

    msg_type getType();
    const int getSize();

    RTKMessageVelocity();
    ~RTKMessageVelocity();
};