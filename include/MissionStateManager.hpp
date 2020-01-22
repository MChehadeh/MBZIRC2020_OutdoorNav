#pragma once
#include "MsgEmitter.hpp"
#include "ROSUnits/IntegerMsg.hpp"
enum outdoor_navigation_states {Idle, AllWallFiresDetected, AllGroundFiresDetected, AllOutdoorFiresDetected};

class MissionStateManager : public msg_emitter
{
private:
    outdoor_navigation_states current_outdoor_navigation_state=outdoor_navigation_states::Idle;
public:
    void updateMissionState(outdoor_navigation_states);
    outdoor_navigation_states getMissionState();
};

extern MissionStateManager MainMissionStateManager;