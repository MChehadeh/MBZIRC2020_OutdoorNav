#pragma once
#include "DataMessage.hpp"
#include "Vector3D.hpp"

class FireLineDescription : public DataMessage{

public:
    Vector3D<float> point1;
    Vector3D<float> point2;

    msg_type getType();
    const int getSize();
    void setFireLineMessage(Vector3D<float>, Vector3D<float>);
    FireLineDescription();
    ~FireLineDescription();
};