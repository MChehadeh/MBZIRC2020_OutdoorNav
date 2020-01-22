#pragma once
#include "Vector3D.hpp"
#include "Rectangle.hpp"
#include "MsgReceiver.hpp"
#include <vector>
#include "print_utility.hpp"
#include "filterPointMsg.hpp"
#include "CollisionFinder.hpp"
#include "Waypoint.hpp"
#include "IntegerMsg.hpp"
#include "EmptyMsg.hpp"
#include "PoseMsg.hpp"
#include "PosesMsg.hpp"
//The following simplest scenario is considered.
// One drone scans the whole building exterior. Identifies the location of all fire sources. Then extinguishing starts.
enum fire_id {wall_fire_gf, wall_fire_ff, wall_fire_sf, last_fire_id = wall_fire_sf};

class navigator_ch3 : public msg_receiver, public msg_emitter{
private:
    double dist_to_wall, max_altitude, min_dist_to_floor, altitude_increment, GF_height, GF_FF_height;
    int external_wall_fire_counter=0;
    Rectangle GF_outline;
    Rectangle SndF_outline;
    Vector3D<double> latest_known_position;
    Vector3D<double> launch_point,landing_point;
    Vector3D<double> yaw_point_of_interest; //This would be the center of the building
    std::vector<Rectangle> scanning_corridors;
    std::vector<Vector3D<double>> fire_loc_at_corridor;
    std::vector<Vector3D<double>> fire_loc_at_building;
    navigator_ch3();
    fire_id findFireID(Vector3D<double> fire_location);
    void addFireLocation(fire_id detected_fire_id, Vector3D<double> fire_location,Vector3D<double> fire_normal); //fire_normal: point1 at fire_location. Unit length is assumed
    double getHeadingToPoint(Vector2D<double> base_point,Vector2D<double> target_point);
    double getHeadingToPoint(Vector3D<double> base_point,Vector3D<double> target_point);
public:
    navigator_ch3(Rectangle t_GF_outline, Rectangle t_SndF_outline, double altitude_increment, double min_dist_to_floor,
    double max_altitude, double dist_to_wall, double GF_FF_height, double GF_height); 
    void updateLaunchPoint(Vector3D<double>);
    void updateLandingPoint(Vector3D<double>);
    std::vector<Waypoint> generateWaypointsToCorridor(); //This will consider launch point
    std::vector<Waypoint> generateWaypointsToCorridor(Vector3D<double> start_point,double corridor_altitude);
    std::vector<Waypoint> generateWaypointsForScanning(Vector3D<double> start_point);
    std::vector<Waypoint> generateFireApproachPath(Vector3D<double> start_point,fire_id target_fire_id);
    std::vector<Waypoint> generateWaypointsToLandingPoint(Vector3D<double> start_point); //This will consider landing point as final point
    double getDistanceToBuilding(Vector3D<double> t_point);
    void receive_msg_data(DataMessage* t_msg) override;
};