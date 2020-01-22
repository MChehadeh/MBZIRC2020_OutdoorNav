// Version: 2.0
// Author: M. CHehadeh
// Date: 22 Jan 2020
// Release note: Added channels for emitter and receiver

#include "MsgEmitter.hpp"

void msg_emitter::add_callback_msg_receiver(msg_receiver* _callback_msg_receiver){
    _list_of_msg_receivers.push_back(_callback_msg_receiver);
    //// std::cout<<"msg_emitter::add_callback_msg_receiver "<<_list_of_msg_receivers.size()<<std::endl;
}

void msg_emitter::emit_message(DataMessage* t_msg){
    std::list<msg_receiver*>::iterator it;
    #ifndef UseEmittingToChannelScheme
    for (it = _list_of_msg_receivers.begin(); it != _list_of_msg_receivers.end(); ++it){
        (*it)->receive_msg_data(t_msg);
    }
    #else
    for (it = _list_of_msg_receivers.begin(); it != _list_of_msg_receivers.end(); ++it){
        (*it)->receive_msg_data(t_msg,default_emitting_channel);
    }
    #endif
}

void msg_emitter::emit_message(DataMessage* t_msg,int t_channel_id){
    std::list<msg_receiver*>::iterator it;
    for (it = _list_of_msg_receivers.begin(); it != _list_of_msg_receivers.end(); ++it){
        (*it)->receive_msg_data(t_msg,t_channel_id);
    }
}

msg_emitter::msg_emitter(){
}

void msg_emitter::setDefaultEmittingChannel(int t_ch){
    this->default_emitting_channel=t_ch;
}

int msg_emitter::getDefaultEmittingChannel(){
    return default_emitting_channel;
}