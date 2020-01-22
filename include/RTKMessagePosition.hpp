#pragma once
#include "DataMessage.hpp"
#include "Vector3D.hpp"
#include "Quaternion.hpp"
#include "common_types.hpp"

class RTKMessagePosition : public DataMessage{

public:
    Vector3D<double> position;
    int id; 

    msg_type getType();
    const int getSize();

    RTKMessagePosition();
    ~RTKMessagePosition();
};