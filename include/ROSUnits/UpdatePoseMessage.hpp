#pragma once
#include "DataMessage.hpp"

class UpdatePoseMessage : public DataMessage{

private:
    float _x, _y, _z, _yaw;
    msg_type _type;

public:

    float getX();
    float getY();
    float getZ();
    float getYaw();
    msg_type getType();
    const int getSize();
    void setPoseMessage(float, float, float, float);
    
    UpdatePoseMessage(float,float,float,float);
    UpdatePoseMessage();
    ~UpdatePoseMessage();
};