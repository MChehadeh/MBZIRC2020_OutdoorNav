#pragma once
#include "DataMessage.hpp"

class IntegerMsg : public DataMessage
{
public:

    IntegerMsg();
    ~IntegerMsg();

    msg_type getType();
    const int getSize();

    int data;
    
};