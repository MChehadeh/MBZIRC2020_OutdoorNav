#include "MissionStateManager.hpp"
MissionStateManager MainMissionStateManager;
void MissionStateManager::updateMissionState(outdoor_navigation_states t_current_state){
    current_outdoor_navigation_state=t_current_state;
    IntegerMsg state_msg;
    state_msg.data=(int)t_current_state;
    emit_message(&state_msg);
}

outdoor_navigation_states MissionStateManager::getMissionState(){
    return current_outdoor_navigation_state;
}
