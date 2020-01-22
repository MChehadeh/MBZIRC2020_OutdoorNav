#include "RTKMessagePosition.hpp"

RTKMessagePosition::RTKMessagePosition() {
}

RTKMessagePosition::~RTKMessagePosition() {

}

const int RTKMessagePosition::getSize()
{
	return sizeof(RTKMessagePosition);
}
msg_type RTKMessagePosition::getType(){
    return msg_type::rtkposition;
}