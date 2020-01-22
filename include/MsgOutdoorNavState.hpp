#pragma once
#include "DataMessage.hpp"
#include "MissionStateManager.hpp"
#include "common_types.hpp"

class MsgOutdoorNavState: public DataMessage{
public:
    outdoor_navigation_states msg_outdoor_navigation_state=outdoor_navigation_states::Idle;
    msg_type getType();
    const int getSize();
};