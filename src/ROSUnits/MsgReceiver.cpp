// Version: 2.0
// Author: M. CHehadeh
// Date: 22 Jan 2020
// Release note: Added channels for emitter and receiver

#include "MsgReceiver.hpp"


void msg_receiver::assign_message_type_ID(msg_type i){
    this->_msg_type=i;
    //// std::cout<<"assign_message_type_ID"<<std::endl;
}

msg_type msg_receiver::get_message_type_ID(){
    //// std::cout<<"get_message_type_ID"<<std::endl;
    return this->_msg_type;
}
msg_receiver::msg_receiver(){
    // std::cout<<"msg_receiver"<<std::endl;
}

void msg_receiver::receive_msg_data(DataMessage* t_msg){
    this->receive_msg_data(t_msg,msg_broadcast_channel);
}
void msg_receiver::receive_msg_data(DataMessage* t_msg,int channel_id){

}
