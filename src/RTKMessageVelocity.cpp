#include "RTKMessageVelocity.hpp"

RTKMessageVelocity::RTKMessageVelocity() {
}

RTKMessageVelocity::~RTKMessageVelocity() {

}
const int RTKMessageVelocity::getSize()
{
	return sizeof(RTKMessageVelocity);
}

msg_type RTKMessageVelocity::getType(){
    return msg_type::rtkvelocity;
}