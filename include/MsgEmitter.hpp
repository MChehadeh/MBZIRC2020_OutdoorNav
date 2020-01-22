// Version: 2.0
// Author: M. CHehadeh
// Date: 22 Jan 2020
// Release note: Added channels for emitter and receiver

#ifndef msg_emitter_H
#define msg_emitter_H
#include <list> 
#include <iterator> 
#include <iostream>
#include "MsgReceiver.hpp"
#include "DataMessage.hpp"

#define UseEmittingToChannelScheme //Please refer to emit_message(DataMessage* t_msg) implementation for details on difference

using namespace std;
class msg_receiver;
class msg_emitter{
private:

protected:
    list<msg_receiver*> _list_of_msg_receivers;
    int default_emitting_channel=0;
public:
    void setDefaultEmittingChannel(int);
    int getDefaultEmittingChannel();
    msg_emitter();
    void add_callback_msg_receiver(msg_receiver* _callback_msg_receiver);
    void emit_message(DataMessage* t_msg);
    void emit_message(DataMessage* t_msg,int t_channel_id);
};
#endif