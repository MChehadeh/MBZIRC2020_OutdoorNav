#include "ROSUnit_Factory.hpp"

ROSUnit_Factory::ROSUnit_Factory(){

}
ROSUnit_Factory::ROSUnit_Factory(ros::NodeHandle& t_nh){
    nh=t_nh;
}
ROSUnit* ROSUnit_Factory::CreateROSUnit(ROSUnit_tx_rx_type t_ros_msg_type_rx_tx,ROSUnit_msg_type t_ros_msg_variant,std::string ROS_path){
    ROSUnit* new_ros_unit_ptr;
    switch (t_ros_msg_variant)
    {
        case ROSUnit_msg_type::ROSUnit_Empty:
        {
            if (t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Client){
                new_ros_unit_ptr=new ROSUnit_EmptyClnt(ROS_path,nh);
            }
            else if(t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Server){
                new_ros_unit_ptr=new ROSUnit_EmptySrv(ROS_path,nh);
            }
            else{
                //TODO: add error: doesnt exist
            }

        }
        break;
        case ROSUnit_msg_type::ROSUnit_Float :
        {
            if (t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Client){
                new_ros_unit_ptr=new ROSUnit_SetFloatClnt(ROS_path,nh);
            }
            else if(t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Server){
                new_ros_unit_ptr=new ROSUnit_SetFloatSrv(ROS_path,nh);
            }
            else if(t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Subscriber){
                new_ros_unit_ptr=new ROSUnit_FloatSub(ROS_path,nh);
            }
            else if(t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Publisher){
                new_ros_unit_ptr=new ROSUnit_FloatPub(ROS_path,nh);
            }
        }
        break;
        case ROSUnit_msg_type::ROSUnit_Int:
        {
            if (t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Client){
                new_ros_unit_ptr=new ROSUnit_SetIntClnt(ROS_path,nh);
            }
            else if(t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Server){
                new_ros_unit_ptr=new ROSUnit_SetIntSrv(ROS_path,nh);
            }
            else{
                //TODO: add error: doesnt exist
            }
        }
        break;
        case ROSUnit_msg_type::ROSUnit_Point2D:
        {
            if (t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Client){
                //TODO: add error: doesnt exist
            }
            else if(t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Server){
                //TODO: add error: doesnt exist
            }
            else if(t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Subscriber){
                new_ros_unit_ptr=new ROSUnit_Point2DSub(ROS_path,nh);
            }
            else if(t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Publisher){
                new_ros_unit_ptr=new ROSUnit_Point2DPub(ROS_path,nh);
            }
        }
        case ROSUnit_msg_type::ROSUnit_Point:
        {
            if (t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Client){
                new_ros_unit_ptr=new ROSUnit_SetPointClnt(ROS_path,nh);
            }
            else if(t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Server){
                new_ros_unit_ptr=new ROSUnit_SetPointSrv(ROS_path,nh);
            }
            else if(t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Subscriber){
                new_ros_unit_ptr=new ROSUnit_PointSub(ROS_path,nh);
            }
            else if(t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Publisher){
                new_ros_unit_ptr=new ROSUnit_PointPub(ROS_path,nh);
            }
        }
        break;
        case ROSUnit_msg_type::ROSUnit_Points:
        {
            if (t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Client){
                new_ros_unit_ptr=new ROSUnit_SetPointsClnt(ROS_path,nh);
            }
            else if(t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Server){
                new_ros_unit_ptr=new ROSUnit_SetPointsSrv(ROS_path,nh);
            }
            else{
                //TODO: add error: doesnt exist
            }
        }
        break;
        case ROSUnit_msg_type::ROSUnit_Pose:
        {
            if (t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Client){
                new_ros_unit_ptr=new ROSUnit_SetPoseClnt(ROS_path,nh);
            }
            else if(t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Server){
                new_ros_unit_ptr=new ROSUnit_SetPoseSrv(ROS_path,nh);
            }
            else{
                //TODO: add error: doesnt exist
            }
        }
        break;
        case ROSUnit_msg_type::ROSUnit_Poses:
        {
            if (t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Client){
                new_ros_unit_ptr=new ROSUnit_SetPosesClnt(ROS_path,nh);
            }
            else if(t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Server){
                new_ros_unit_ptr=new ROSUnit_SetPosesSrv(ROS_path,nh);
            }
            else{
                //TODO: add error: doesnt exist
            }
        }
        break;
        case ROSUnit_msg_type::ROSUnit_Vector:
        {
            if (t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Client){
                new_ros_unit_ptr=new ROSUnit_SetVectorClnt(ROS_path,nh);
            }
            else if(t_ros_msg_type_rx_tx==ROSUnit_tx_rx_type::Server){
                new_ros_unit_ptr=new ROSUnit_SetVectorSrv(ROS_path,nh);
            }
            else{
                //TODO: add error: doesnt exist
            }
        }
        break;
    }
    if (new_ros_unit_ptr==nullptr){
        throw "ERROR: new_ros_unit_ptr is null. Terminating...";
    }
    return new_ros_unit_ptr;
}
