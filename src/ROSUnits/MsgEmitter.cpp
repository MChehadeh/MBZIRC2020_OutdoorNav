// Version: 1.0
// Author: Pedro Henrique R. P. B. Silva
// Date: 19 November 2019

#include "MsgEmitter.hpp"

void msg_emitter::add_callback_msg_receiver(msg_receiver* _callback_msg_receiver){
    _list_of_msg_receivers.push_back(_callback_msg_receiver);
}

void msg_emitter::emit_message(DataMessage* t_msg){
    std::list<msg_receiver*>::iterator it;
    for (it = _list_of_msg_receivers.begin(); it != _list_of_msg_receivers.end(); ++it){
        (*it)->receive_msg_data(t_msg);
    }
}
msg_emitter::msg_emitter(){
}

