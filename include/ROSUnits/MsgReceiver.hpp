// Version: 1.0
// Author: Pedro Henrique R. P. B. Silva
// Date: 19 November 2019

#ifndef msg_receiver_H
#define msg_receiver_H
#include <iostream>
#include "common_types.hpp"
#include "DataMessage.hpp"

class msg_receiver {
    private:
    msg_type _msg_type;
    public:
    msg_receiver();
    void assign_message_type_ID(msg_type i);
    msg_type get_message_type_ID();
    virtual void receive_msg_data(DataMessage* t_msg)=0;
};
#endif