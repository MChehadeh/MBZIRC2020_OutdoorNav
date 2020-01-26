#include "ros/ros.h"
//#include "ROSUnit_FireLocationServer.hpp"
#include "CollisionFinder.hpp"
#include "Global2Inertial.hpp"
#include "CollisionFilter.hpp"
#include "navigator_ch3.hpp"
#include "MissionStateManager.hpp"
//Environment Model
#include "Line2D.hpp"
#include "Rectangle.hpp"
#include "Vector2D.hpp"
//ROS Units
#include "ROSUnit_SetVectorSrv.hpp"
#include "ROSUnit_G2InertialTransform.hpp"
#include "ROSUnit_Optitrack.hpp"
#include "ROSUnit_RTK1.hpp"
#include "ROSUnit_RTK2.hpp"
#include "ROSUnit_Xsens.hpp"
#include "ROSUnits/ROSUnit_Factory.hpp"
//Environment Model Parameters
const double altitude_increment=2.; //Altitude gained after every run around the building
const double min_dist_to_floor=1.8;//This is the switch altitude+GF_FF_height for smaller run around SndF
const double max_altitude=15;
const double dist_to_wall=1.5;//Gap to wall for the corridor
const double GF_FF_height=9;//Height for GF+FF
const double GF_height=4.5;
const double SndF_height=3;
int main(int argc, char **argv)
{
  //*********************************************************************************
  //***************************ROS SETUP****************************************
  //*********************************************************************************
  ros::init(argc, argv, "outdoor_navigation");
  ros::NodeHandle nh;
  ros::Rate loop_rate(100);
  ROSUnit_Factory ROSUnit_Factory_main{nh};

  //*********************************************************************************
  //************************ Environement Model Setup *******************************
  //*********************************************************************************
  //Challenge 3 Navigator
  Vector2D<double> side1_GF_p1,side1_GF_p2,side2_GF_p2;
  side1_GF_p1.x=0;
  side1_GF_p1.y=0;
  side1_GF_p2.x=5;
  side1_GF_p2.y=0;
  side2_GF_p2.x=0;
  side2_GF_p2.y=10;

  Vector2D<double> side1_SndF_p1,side1_SndF_p2,side2_SndF_p2;
  side1_SndF_p1.x=0;
  side1_SndF_p1.y=0;
  side1_SndF_p2.x=5;
  side1_SndF_p2.y=0;
  side2_SndF_p2.x=0;
  side2_SndF_p2.y=5;

  Line2D side1_GF,side2_GF,side1_SndF,side2_SndF;
  side1_GF.setPoint1(side1_GF_p1);
  side1_GF.setPoint2(side1_GF_p2);
  side2_GF.setPoint1(side1_GF_p1);
  side2_GF.setPoint2(side2_GF_p2);

  side1_SndF.setPoint1(side1_SndF_p1);
  side1_SndF.setPoint2(side1_SndF_p2);
  side2_SndF.setPoint1(side1_SndF_p1);
  side2_SndF.setPoint2(side2_SndF_p2);

  Rectangle GF,SndF;
  
  GF.updateRectangleSides(side1_GF,side2_GF);
  SndF.updateRectangleSides(side1_SndF,side2_SndF);

  //Navigation Space Model
  navigator_ch3 navigator_ch3_main{GF,SndF,altitude_increment,min_dist_to_floor,max_altitude,dist_to_wall,GF_FF_height,GF_height};
  Vector3D<double> launch_point,landing_point;
  launch_point.x=-10;
  launch_point.y=1;
  launch_point.z=0;
  landing_point=launch_point;
  navigator_ch3_main.updateLaunchPoint(launch_point);
  navigator_ch3_main.updateLandingPoint(landing_point);

  //Collision Space Model
  CollisionFinder fireLocationFinder{GF, SndF, GF_FF_height, SndF_height};
  CollisionFilter fireLocationFilter;

  //Add fire locations for testing.
  filterPointMsg fire_1,fire_2,fire_3;
  Vector3D<float> fire_1_loc,fire_2_loc,fire_3_loc;
  fire_1_loc.x=0;
  fire_1_loc.y=3;
  fire_1_loc.z=3;
  fire_1.filterPoint=fire_1_loc;
  fire_1.side_of_hit=building_sides::side1;
  fire_2_loc.x=3;
  fire_2_loc.y=0;
  fire_2_loc.z=6;
  fire_2.filterPoint=fire_2_loc;
  fire_2.side_of_hit=building_sides::side2;
  fire_3_loc.x=5;
  fire_3_loc.y=3;
  fire_3_loc.z=11;
  fire_3.filterPoint=fire_3_loc;
  fire_3.side_of_hit=building_sides::side3;

  navigator_ch3_main.receive_msg_data(&fire_1);
  navigator_ch3_main.receive_msg_data(&fire_2);
  navigator_ch3_main.receive_msg_data(&fire_3);
  //*********************************************************************************
  //*************************** Communication Setup *********************************
  //*********************************************************************************
  // Position and Orientation Sources
  ROSUnit* ROSUnit_uav_orientation = ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Subscriber,ROSUnit_msg_type::ROSUnit_Point,"uav_control/uav_orientation");
  ROSUnit* ROSUnit_uav_position = ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Subscriber,ROSUnit_msg_type::ROSUnit_Point,"uav_control/uav_position");
  ROSUnit_uav_orientation->setEmittingChannel((int)navigator_ch3::receiving_channels::UAV_Orientation);
  ROSUnit_uav_position->setEmittingChannel((int)navigator_ch3::receiving_channels::UAV_Position);

  ROSUnit* ROSUnit_estimatedFireDirection = ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Server,ROSUnit_msg_type::ROSUnit_Vector,"outdoor_navigation/set_fire_direction");
  ROSUnit_uav_position->add_callback_msg_receiver(&navigator_ch3_main);
  ROSUnit_uav_orientation->add_callback_msg_receiver(&navigator_ch3_main);
  ROSUnit_estimatedFireDirection->add_callback_msg_receiver(&fireLocationFinder);//OK
  fireLocationFinder.add_callback_msg_receiver(&fireLocationFilter);//OK
  fireLocationFilter.add_callback_msg_receiver(&navigator_ch3_main);//OK
  ROSUnit* ROSUnit_update_outdoor_nav_state_instance=ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Client,ROSUnit_msg_type::ROSUnit_Int,"ex_bldg_fire_mm/update_outdoor_nav_state");
  MainMissionStateManager.add_callback_msg_receiver(ROSUnit_update_outdoor_nav_state_instance);//OK

  ROSUnit* ROSUnit_upload_uav_fire_paths=ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Server,ROSUnit_msg_type::ROSUnit_Int,"outdoor_navigation/upload_uav_fire_paths");
  ROSUnit* ROSUnit_upload_uav_scan_path=ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Server,ROSUnit_msg_type::ROSUnit_Empty,"outdoor_navigation/upload_uav_scan_path");
  ROSUnit* ROSUnit_uav_control_set_path=ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Client,ROSUnit_msg_type::ROSUnit_Poses,"uav_control/set_path");
  ROSUnit* ROSUnit_distance_to_fire=ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Publisher,ROSUnit_msg_type::ROSUnit_Float,"outdoor_navigation/distance_to_fire");
  ROSUnit_upload_uav_fire_paths->add_callback_msg_receiver(&navigator_ch3_main);//OK
  ROSUnit_upload_uav_scan_path->add_callback_msg_receiver(&navigator_ch3_main);//OK
  navigator_ch3_main.add_callback_msg_receiver(ROSUnit_uav_control_set_path);//OK
  navigator_ch3_main.add_callback_msg_receiver(ROSUnit_distance_to_fire);

  while (ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}