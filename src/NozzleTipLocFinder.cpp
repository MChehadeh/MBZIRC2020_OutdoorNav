#include "NozzleTipLocFinder.hpp"

void NozzleTipLocFinder::receive_msg_data(DataMessage* t_msg){
    //if pose
    
    //if request dist to fire (wall)
    Vector3D<double> nozzle_base_vector,nozzle_loc;
    nozzle_base_vector.x=nozzle_offset_to_center;
    RotationMatrix3by3 rot_matrix;
    rot_matrix.Update(UAV_attitude_latest);
    nozzle_loc=rot_matrix.TransformVector(nozzle_base_vector);
    nozzle_loc=nozzle_loc+UAV_location_latest;
    emit_message();//TODO
}
