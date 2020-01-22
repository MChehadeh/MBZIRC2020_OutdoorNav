#pragma once
#include "DataMessage.hpp"

class EmptyMsg : public DataMessage
{
public:

    EmptyMsg();
    ~EmptyMsg();

    msg_type getType();
    const int getSize();    
};