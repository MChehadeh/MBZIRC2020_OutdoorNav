#include "Global2Inertial.hpp"

// const float PI = atan(1.0)*4.0;

// float MeasureGPStoMeters(float lat1, float lon1, float lat2, float lon2)
// {  
//     float R    = 6378.137; // Radius of earth in km
//     float dLat = lat2*(PI/180) - lat1*(PI/180);
//     float dLon = lon2*(PI/180) - lon1*(PI/180);
//     float a    = sin(dLat/2)*sin(dLat/2) + cos(lat1*PI/180)*cos(lat2*PI/180)*sin(dLon/2)*sin(dLon/2);
//     float c    = 2 * atan2(sqrt(a), sqrt(1-a));
//     float d    = R * c;
//     return d*1000; // meters
// }
Global2Inertial::Global2Inertial(){
    //TODO: Ensure altitude is calibrated
    calib_point1.x=0;
    calib_point1.y=0;
    calib_point1.z=0;
    calib_point2.x=0;
    calib_point2.y=0;
    calib_point2.z=0;
    calibrated_reference_inertial_heading=45.*(M_1_PI/180.);
    Vector3D<double> calib_points_diff = calib_point2 - calib_point1;
    calibrated_global_to_inertial_angle = atan2(calib_points_diff.y, calib_points_diff.x);
    antenna_pose.x=0.;
    antenna_pose.y=0.1;
    antenna_pose.z=0.1;
}
void Global2Inertial::receive_msg_data(DataMessage* t_msg)
{
    if(t_msg->getType() == msg_type::optitrack){ //TODO: Refactor message types

        //TODO implement for GPS
        OptitrackMessage* opti_msg = ((OptitrackMessage*)t_msg);
        Vector3D<double> pos_point = opti_msg->getPosition();
        Quaternion _bodyAtt = opti_msg->getAttitudeHeading();
        //HeadingMsg _bodyHeading = this->getHeading(_bodyAtt);
        Vector3D<float> results = transformPoint(pos_point);
        Vector3D<float> att_vec = getEulerfromQuaternion(_bodyAtt);
        AttitudeMsg _eulerAtt;
        HeadingMsg _bodyHeading;
        _eulerAtt.pitch = att_vec.y;
        _eulerAtt.roll = att_vec.x;
        _bodyHeading.yaw = att_vec.z;
        PoseMsg results_msg;
        results_msg.pose.x = results.x;
        results_msg.pose.y = results.y;
        results_msg.pose.z = results.z;
        
        this->emit_message((DataMessage*)&results_msg);
        //this->emit_message((DataMessage*)&_eulerAtt);
        //this->emit_message((DataMessage*)&_bodyHeading);
    }
    else if (t_msg->getType()==msg_type::rtkposition){
        #ifdef planC_dual_RTK
        RTKMessagePosition* rtk_msg = ((RTKMessagePosition*)t_msg);
        #error planC_dual_RTK is not implemented yet
        //TODO: PlanC is not implemented
        #elif defined(planB_single_RTK)
        RTKMessagePosition* rtk_msg = ((RTKMessagePosition*)t_msg);
        if (rtk_msg->id==1){
            RotationMatrix3by3 antenna_body_aligner;
            antenna_body_aligner.Update(last_known_orientation);
            Vector3D<double> rotated_antenna_position=antenna_body_aligner.TransformVector(antenna_pose);
            Vector3D<double> t_global_antenna_position=rtk_msg->position;
            Vector3D<double> t_global_drone_position=t_global_antenna_position-rotated_antenna_position;
            Vector3D<float> t_inertial_drone_position = transformPoint(t_global_drone_position);
            PoseMsg results_msg;
            results_msg.pose.x = t_inertial_drone_position.x;
            results_msg.pose.y = t_inertial_drone_position.y;
            results_msg.pose.z = t_inertial_drone_position.z;
            this->emit_message((DataMessage*)&results_msg);
        }
        #endif
        
    }
    else if (t_msg->getType()==msg_type::POSITION){//TODO: XSesns position

    }
    else if (t_msg->getType()==msg_type::ATTITUDE){
        AttitudeMsg* att_msg = ((AttitudeMsg*)t_msg);
        last_known_orientation.x=att_msg->pitch;
        last_known_orientation.y=att_msg->roll;
    }
    else if (t_msg->getType()==msg_type::HEADING){
        HeadingMsg* hdng_msg = ((HeadingMsg*)t_msg);
        last_known_orientation.z=hdng_msg->yaw;
        HeadingMsg calibrated_heading_msg;
        calibrated_heading_msg.yaw=last_known_orientation.z-calibrated_reference_inertial_heading;
        emit_message((DataMessage*)&calibrated_heading_msg);
    }
}

Vector3D<double> Global2Inertial::transformPoint(Vector3D<double> t_input_point){
        
    Vector3D<double> euler_calib;
    euler_calib.z = calibrated_global_to_inertial_angle;

    Vector3D<double> origin = calib_point1;
    Vector3D<double> calibrated_input_point;
    
    calibrated_input_point = t_input_point - origin;
    RotationMatrix3by3 G_I_rot_matrix;

    G_I_rot_matrix.Update(euler_calib);

    calibrated_input_point = G_I_rot_matrix.TransformVector(calibrated_input_point);
 
    G_I_rot_matrix.Transpose();
    calibrated_input_point = G_I_rot_matrix.TransformVector(calibrated_input_point);

    Vector3D<double> t_results;
    t_results.x = calibrated_input_point.x;
    t_results.y = calibrated_input_point.y;
    t_results.z = calibrated_input_point.z;

    return t_results;
}

Vector3D<double> Global2Inertial::getEulerfromQuaternion(Quaternion q){

    // roll (x-axis rotation)
    double sinr_cosp = +2.0 * (q.w * q.x + q.y * q.z);
    double cosr_cosp = +1.0 - 2.0 * (q.x * q.x + q.y * q.y);
    Vector3D<float> _euler;
    _euler.x = atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = +2.0 * (q.w * q.y - q.z * q.x);
    if (fabs(sinp) >= 1)
        _euler.y = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    else
        _euler.y = asin(sinp);

    // yaw (z-axis rotation)
    double siny_cosp = +2.0 * (q.w * q.z + q.x * q.y);
    double cosy_cosp = +1.0 - 2.0 * (q.y * q.y + q.z * q.z);  
    _euler.z = atan2(siny_cosp, cosy_cosp);

    return _euler;
}

HeadingMsg Global2Inertial::getHeading(Quaternion t_bodyAtt)
{
    Vector3D<float> rpy = getEulerfromQuaternion(t_bodyAtt);
    HeadingMsg t_heading_msg;
    t_heading_msg.yaw = rpy.z;

    return t_heading_msg;
}