// Version: 2.0
// Author: M. CHehadeh
// Date: 22 Jan 2020
// Release note: Added channels for emitter and receiver
#pragma once
#include <list> 
#include <iterator> 
#include <iostream>
#include "MsgReceiver.hpp"
#include "DataMessage.hpp"

using namespace std;
class msg_receiver;
class msg_emitter{
private:

protected:
    list<msg_receiver*> _list_of_msg_receivers;
    int emitting_channel=msg_broadcast_channel;
public:
    void setEmittingChannel(int);
    int getEmittingChannel();
    msg_emitter();
    void add_callback_msg_receiver(msg_receiver* _callback_msg_receiver);
    void emit_message(DataMessage* t_msg);
    void emit_message(DataMessage* t_msg,int t_channel_id);
};
