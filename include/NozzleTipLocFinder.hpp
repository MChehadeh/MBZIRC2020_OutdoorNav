#pragma once
#include "MsgEmitter.hpp"
#include "MsgReceiver.hpp"
#include "Vector3D.hpp"
#include "RotationMatrix3by3.hpp"

class NozzleTipLocFinder : public msg_emitter, public msg_receiver {
private:
    const double nozzle_offset_to_center=0.8; //TODO refactor
    Vector3D<double> UAV_location_latest;
    Vector3D<double> UAV_attitude_latest;
public:
    void receive_msg_data(DataMessage*);
};