// Version: 1.0
// Author: Pedro Henrique R. P. B. Silva
// Date: 19 November 2019

#pragma once
#include <list>
#include "common_types.hpp"

class DataMessage {

public:
    
    virtual msg_type getType() = 0;
    virtual const int getSize() = 0;

    DataMessage();
    ~DataMessage();
};