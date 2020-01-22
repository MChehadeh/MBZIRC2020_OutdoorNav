#include "MsgOutdoorNavState.hpp"

msg_type MsgOutdoorNavState::getType(){
    return msg_type::OutdoorNavState;
}
const int MsgOutdoorNavState::getSize(){
    const int size_msg=4; //TODO Refactor
    return size_msg;
}