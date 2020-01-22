#pragma once
#include "DataMessage.hpp"
#include "Vector2D.hpp"

class Vector2DMsg : public DataMessage
{
public:

    Vector2DMsg();
    ~Vector2DMsg();

    msg_type getType();
    const int getSize();

    Vector2D<float> data;
};