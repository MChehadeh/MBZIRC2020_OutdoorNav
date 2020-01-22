// Version: 1.0
// Author: Pedro Henrique R. P. B. Silva
// Date: 19 November 2019

#ifndef msg_emitter_H
#define msg_emitter_H
#include <list> 
#include <iterator> 
#include <iostream>
#include "MsgReceiver.hpp"
#include "DataMessage.hpp"

using namespace std;
class msg_receiver;
class msg_emitter{
protected:
    list<msg_receiver*> _list_of_msg_receivers;
public:
    msg_emitter();
    void add_callback_msg_receiver(msg_receiver* _callback_msg_receiver);
    void emit_message(DataMessage* t_msg);
};
#endif