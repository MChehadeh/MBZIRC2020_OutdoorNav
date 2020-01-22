#pragma once
#include "ros/ros.h"
#include "ROSUnit.hpp"
#include "ROSUnit_FloatPub.hpp"
#include "ROSUnit_FloatSub.hpp"
#include "ROSUnit_Point2DPub.hpp"
#include "ROSUnit_Point2DSub.hpp"
#include "ROSUnit_PointPub.hpp"
#include "ROSUnit_PointSub.hpp"
#include "ROSUnit_EmptyClnt.hpp"
#include "ROSUnit_EmptySrv.hpp"
#include "ROSUnit_SetFloatClnt.hpp"
#include "ROSUnit_SetFloatSrv.hpp"
#include "ROSUnit_SetIntClnt.hpp"
#include "ROSUnit_SetIntSrv.hpp"
#include "ROSUnit_SetPointClnt.hpp"
#include "ROSUnit_SetPointsClnt.hpp"
#include "ROSUnit_SetPointSrv.hpp"
#include "ROSUnit_SetPointsSrv.hpp"
#include "ROSUnit_SetPoseClnt.hpp"
#include "ROSUnit_SetPosesClnt.hpp"
#include "ROSUnit_SetPoseSrv.hpp"
#include "ROSUnit_SetPosesSrv.hpp"
#include "ROSUnit_SetVectorClnt.hpp"
#include "ROSUnit_SetVectorSrv.hpp"

#include <string>
enum ROSUnit_tx_rx_type {Client,Subscriber,Server,Publisher};
enum ROSUnit_msg_type {ROSUnit_Empty,ROSUnit_Float,ROSUnit_Int,ROSUnit_Point,ROSUnit_Points,ROSUnit_Pose,ROSUnit_Poses,ROSUnit_Vector,ROSUnit_Point2D};

class ROSUnit_Factory {
private:
    ros::NodeHandle nh;
    ROSUnit_Factory();
public:
    ROSUnit_Factory(ros::NodeHandle&);
    ROSUnit* CreateROSUnit(ROSUnit_tx_rx_type,ROSUnit_msg_type,std::string ROS_path);
};