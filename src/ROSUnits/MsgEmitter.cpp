// Version: 2.0
// Author: M. CHehadeh
// Date: 22 Jan 2020
// Release note: Added channels for emitter and receiver

#include "MsgEmitter.hpp"
using namespace std;

void msg_emitter::add_callback_msg_receiver(msg_receiver* _callback_msg_receiver){
    _list_of_msg_receivers.push_back(_callback_msg_receiver);
    _list_of_receivers_mask_unicast.push_back(0);
    //// std::cout<<"msg_emitter::add_callback_msg_receiver "<<_list_of_msg_receivers.size()<<std::endl;
}

void msg_emitter::add_callback_msg_receiver(msg_receiver* _callback_msg_receiver,int associated_publishing_channel){
    _list_of_msg_receivers.push_back(_callback_msg_receiver);
    _list_of_receivers_mask_unicast.push_back(associated_publishing_channel);
    //// std::cout<<"msg_emitter::add_callback_msg_receiver "<<_list_of_msg_receivers.size()<<std::endl;
}

void msg_emitter::emit_message(DataMessage* t_msg){
    if (this->emitting_channel!=msg_broadcast_channel){
        this->emit_message(t_msg,this->emitting_channel);
    }
    else{
        
        for (int i = 0; i < _list_of_msg_receivers.size(); ++i){
            _list_of_msg_receivers[i]->receive_msg_data(t_msg);
        }
    }

}

void msg_emitter::emit_message(DataMessage* t_msg,int t_channel_id){
    std::list<msg_receiver*>::iterator it;
    for (int i = 0; i < _list_of_msg_receivers.size(); ++i){
        _list_of_msg_receivers[i]->receive_msg_data(t_msg,t_channel_id);
    }
}

void msg_emitter::emit_message_unicast(DataMessage* t_msg,int t_unicast_mask){
    for (int i = 0; i < _list_of_msg_receivers.size(); ++i){
        if (t_unicast_mask==_list_of_receivers_mask_unicast[i]){
             _list_of_msg_receivers[i]->receive_msg_data(t_msg);
        }
    }
}
void msg_emitter::emit_message_unicast(DataMessage* t_msg,int t_unicast_mask,int t_channel_id){
    for (int i = 0; i < _list_of_msg_receivers.size(); ++i){
        if (t_unicast_mask==_list_of_receivers_mask_unicast[i]){
             _list_of_msg_receivers[i]->receive_msg_data(t_msg,t_channel_id);
        }
    }
}
msg_emitter::msg_emitter(){
}

void msg_emitter::setEmittingChannel(int t_ch){
    this->emitting_channel=t_ch;
}

int msg_emitter::getEmittingChannel(){
    return emitting_channel;
}