#include "navigator_ch3.hpp"
#define show_internals
using namespace std;
navigator_ch3::navigator_ch3(){
}

void navigator_ch3::receive_msg_data(DataMessage* t_msg)
{
    if (t_msg->getType()==msg_type::FILTER_POINT){
        filterPointMsg* tmp = ((filterPointMsg*) t_msg);
        Vector3D<double> norm_vec;
        norm_vec = CollisionFinder::getNormalVector(tmp->side_of_hit);
        fire_id detected_fire_id = this->findFireID(tmp->filterPoint);
        this->addFireLocation(detected_fire_id, tmp->filterPoint,norm_vec);
    }
    else if (t_msg->getType()==msg_type::INTEGER) //TODO: Refactor to reflect fire id path request
    {
        std::vector<Waypoint> pathToFire=this->generateFireApproachPath(latest_known_position,static_cast<fire_id>(((IntegerMsg*)t_msg)->data));
        PosesMsg t_wpts;
        for (int i=0;i<pathToFire.size();i++){
            Pose t_wp_pose;
            t_wp_pose.x=pathToFire[i].position.x;
            t_wp_pose.y=pathToFire[i].position.y;
            t_wp_pose.z=pathToFire[i].position.z;
            t_wp_pose.yaw=pathToFire[i].yaw;
            t_wpts.p.poses.push_back(t_wp_pose);
        }
        emit_message(&t_wpts);
    }
    else if (t_msg->getType()==msg_type::EMPTY){ //TODO: Refactor to reflect scan path request

        std::vector<Waypoint> scanning_path=this->generateWaypointsToCorridor(launch_point,scanning_corridors[0].altitude);
        std::vector<Waypoint> t_scanning_path_on_corridor=this->generateWaypointsForScanning(scanning_path.end()->position);
        for (int i=0;i<t_scanning_path_on_corridor.size();i++){
            scanning_path.push_back(t_scanning_path_on_corridor[i]);
        }
        PosesMsg t_wpts;
        for (int i=0;i<scanning_path.size();i++){
            Pose t_wp_pose;
            t_wp_pose.x=scanning_path[i].position.x;
            t_wp_pose.y=scanning_path[i].position.y;
            t_wp_pose.z=scanning_path[i].position.z;
            t_wp_pose.yaw=scanning_path[i].yaw;
            t_wpts.p.poses.push_back(t_wp_pose);
        }
        emit_message(&t_wpts);
    }
    else if(t_msg->getType() == msg_type::POSE)
    {
        latest_known_position.x = ((PoseMsg*)t_msg)->pose.x;
        latest_known_position.y = ((PoseMsg*)t_msg)->pose.y;
        latest_known_position.z = ((PoseMsg*)t_msg)->pose.z;
        //Find tip distance to wall
        Vector3D<double> nozzle_base_vector,nozzle_loc;
        nozzle_base_vector.x=nozzle_offset_to_center;
        // TODO Compensate for heading
        //RotationMatrix3by3 rot_matrix;
        //rot_matrix.Update(UAV_attitude_latest);
        //nozzle_loc=rot_matrix.TransformVector(nozzle_base_vector);
        nozzle_loc=nozzle_loc+latest_known_position;
        FloatMsg distance_to_wall_msg;
        distance_to_wall_msg.data=(float)this->getDistanceToBuilding(nozzle_loc);
        emit_message(&distance_to_wall_msg);
    }

}

navigator_ch3::navigator_ch3(Rectangle t_GF, Rectangle t_SndF, double altitude_increment, double min_dist_to_floor,
double max_altitude, double dist_to_wall, double t_GF_FF_height, double t_GF_height)
{
    //Initialize variables
    Vector3D<double> null_vec;
    for (int i=0; i<=last_fire_id; i++){
        fire_loc_at_corridor.push_back(null_vec);
    }
    GF_height = t_GF_height;
    GF_FF_height = t_GF_FF_height;
    //Generate scanning waypoints
    Rectangle base_corridor_gf;
    base_corridor_gf = t_GF;

    base_corridor_gf.scaleBy((dist_to_wall*2+t_GF.getSide1().getLength())/t_GF.getSide1().getLength(),rect_sides::side1);
    base_corridor_gf.scaleBy((dist_to_wall*2+t_GF.getSide2().getLength())/t_GF.getSide2().getLength(),rect_sides::side2);
    Vector2D<double> offset_floor_outline;
    offset_floor_outline = t_GF.getCenter() - base_corridor_gf.getCenter();
    base_corridor_gf.translateBy(offset_floor_outline);
    Rectangle base_corridor_sndf;
    base_corridor_sndf = t_SndF;
    base_corridor_sndf.scaleBy((dist_to_wall*2+t_SndF.getSide1().getLength())/t_SndF.getSide1().getLength(),rect_sides::side1);
    base_corridor_sndf.scaleBy((dist_to_wall*2+t_SndF.getSide2().getLength())/t_SndF.getSide2().getLength(),rect_sides::side2);
    offset_floor_outline = t_SndF.getCenter() - base_corridor_sndf.getCenter();
    base_corridor_sndf.translateBy(offset_floor_outline);

    for (int i=1; (i*altitude_increment)<=(GF_FF_height+min_dist_to_floor); i++){
        Rectangle t_corridor = base_corridor_gf;
        t_corridor.altitude = i*altitude_increment;
        scanning_corridors.push_back(t_corridor);
    }
    for (int i=1; (i*altitude_increment + GF_FF_height + min_dist_to_floor)<=(max_altitude); i++){
        Rectangle t_corridor = base_corridor_sndf;
        t_corridor.altitude = i*altitude_increment + GF_FF_height + min_dist_to_floor;
        scanning_corridors.push_back(t_corridor);
    }
} 


std::vector<Waypoint> navigator_ch3::generateFireApproachPath(Vector3D<double> start_point,fire_id target_fire_id)
{
    std::vector<Waypoint> t_generated_waypoints;
    t_generated_waypoints = this->generateWaypointsToCorridor(start_point,fire_loc_at_corridor[(int)target_fire_id].z);
    Vector2D<double> first_wp_on_corridor;
    first_wp_on_corridor.x = t_generated_waypoints[1].position.x;
    first_wp_on_corridor.y = t_generated_waypoints[1].position.y;
    Vector2D<double> final_wp_on_corridor;
    final_wp_on_corridor.x = fire_loc_at_corridor[(int)target_fire_id].x;
    final_wp_on_corridor.y = fire_loc_at_corridor[(int)target_fire_id].y;
    vector<Vector2D<double>> wp_on_corridor_2d;
    wp_on_corridor_2d = scanning_corridors[0].generatePathSegmentFromTwoPoint(first_wp_on_corridor, final_wp_on_corridor);
    for (int i=1; i<wp_on_corridor_2d.size(); i++) //i=1 to avoid redundancy
    {
        Waypoint t_wp_3d;
        t_wp_3d.position.x = wp_on_corridor_2d[i].x;
        t_wp_3d.position.y = wp_on_corridor_2d[i].y;
        t_wp_3d.position.z = fire_loc_at_corridor[(int)target_fire_id].z;
        t_wp_3d.yaw=getHeadingToPoint(t_wp_3d.position,fire_loc_at_building[(int)target_fire_id]);
        t_generated_waypoints.push_back(t_wp_3d);
    }
    return t_generated_waypoints;
}
std::vector<Waypoint> navigator_ch3::generateWaypointsForScanning(Vector3D<double> start_point)
{
    std::vector<Waypoint> t_generated_waypoints;
    Vector2D<double> start_point_2d;
    start_point_2d.x = start_point.x;
    start_point_2d.y = start_point.y;
    for (int i=0; i<scanning_corridors.size(); i++)
    {
        std::vector<Vector2D<double>> res_path;
        res_path = scanning_corridors[i].generateClosedPathFromStartingPoint(start_point_2d);
        for (int j=0; j<res_path.size(); j++){
            Waypoint t_wp;
            t_wp.position.x = res_path[j].x;
            t_wp.position.y = res_path[j].y;
            t_wp.position.z = scanning_corridors[i].altitude;
            t_wp.yaw=getHeadingToPoint(res_path[j],scanning_corridors[i].getCenter());
            t_generated_waypoints.push_back(t_wp);
        }
    }
    return t_generated_waypoints;
}

void navigator_ch3::updateLaunchPoint(Vector3D<double> t_launch_point)
{
    launch_point = t_launch_point;
}

void navigator_ch3::updateLandingPoint(Vector3D<double> t_landing_point){
    landing_point= t_landing_point;
}

fire_id navigator_ch3::findFireID(Vector3D<double> fire_location)
{
    if (fire_location.z<GF_height){
        return fire_id::wall_fire_gf;
    }
    else if (fire_location.z>GF_FF_height){
        return fire_id::wall_fire_sf;
    }
    else {
        return fire_id::wall_fire_ff;
    }
    return fire_id::last_fire_id;
}

std::vector<Waypoint> navigator_ch3::generateWaypointsToCorridor()
{
    return generateWaypointsToCorridor(launch_point,scanning_corridors[0].altitude);
}
    
std::vector<Waypoint> navigator_ch3::generateWaypointsToCorridor(Vector3D<double> start_point,double corridor_altitude)
{
    std::vector<Waypoint> t_generated_waypoints;
    Vector2D<double> GF_center=GF_outline.getCenter();
    Vector2D<double> SndF_center=SndF_outline.getCenter();
    //First waypoint for altitude adjustment
    Waypoint t_altitude_adj;
    t_altitude_adj.position = start_point;
    t_altitude_adj.position.z = corridor_altitude;
    Vector2D<double> t_3d_to_2d;
    t_3d_to_2d.x=t_altitude_adj.position.x;
    t_3d_to_2d.y=t_altitude_adj.position.y;
    if (corridor_altitude>this->GF_FF_height){
        t_altitude_adj.yaw=getHeadingToPoint(t_3d_to_2d,SndF_center);
    }
    else{
        t_altitude_adj.yaw=getHeadingToPoint(t_3d_to_2d,GF_center);
    }
    
    t_generated_waypoints.push_back(t_altitude_adj);
    //Second waypoint on the corridor
    Vector2D<double> projected_start_point;
    projected_start_point.x = start_point.x;
    projected_start_point.y = start_point.y;
    Rectangle t_corridor;
    t_corridor = scanning_corridors[0];
    Waypoint closest_point_on_corridor;
    Vector2D<double> closest_point_on_corridor_2d = t_corridor.getClosestPoint(projected_start_point);
    closest_point_on_corridor.position.x = closest_point_on_corridor_2d.x;
    closest_point_on_corridor.position.y = closest_point_on_corridor_2d.y;
    closest_point_on_corridor.position.z = corridor_altitude;
    if (corridor_altitude>this->GF_FF_height){
        closest_point_on_corridor.yaw=getHeadingToPoint(closest_point_on_corridor_2d,SndF_center);
    }
    else{
        closest_point_on_corridor.yaw=getHeadingToPoint(closest_point_on_corridor_2d,GF_center);
    }
    t_generated_waypoints.push_back(closest_point_on_corridor);
    return t_generated_waypoints;
}

std::vector<Waypoint> navigator_ch3::generateWaypointsToLandingPoint(Vector3D<double> start_point){
    std::vector<Waypoint> generated_waypoints;
    generated_waypoints=this->generateWaypointsToCorridor(start_point,start_point.z);
    Rectangle used_corridor;
    used_corridor.altitude=start_point.z;
    if (start_point.z>this->GF_FF_height+min_dist_to_floor){
        used_corridor=SndF_outline;
    }
    else{
        used_corridor=GF_outline;
    }
    Vector2D<double> start_point_2d;
    start_point_2d.x=start_point.x;
    start_point_2d.y=start_point.y;
    Vector2D<double> landing_point_2d;
    landing_point_2d.x=landing_point.x;
    landing_point_2d.y=landing_point.y;
    Vector2D<double> start_point_on_corridor_2d=used_corridor.getClosestPoint(start_point_2d);
    Vector2D<double> end_point_on_corridor_2d=used_corridor.getClosestPoint(landing_point_2d);
    std::vector<Vector2D<double>> path_on_corridor= used_corridor.generatePathSegmentFromTwoPoint(start_point_on_corridor_2d,end_point_on_corridor_2d);
    
    for (int i=0;i<path_on_corridor.size();i++){
        Waypoint t_wp;
        Vector3D<double> t_pos_wp;
        t_pos_wp.x=path_on_corridor[i].x;
        t_pos_wp.y=path_on_corridor[i].y;
        t_pos_wp.z=start_point.z;
        t_wp.position=t_pos_wp;
        t_wp.yaw=getHeadingToPoint(t_wp.position,landing_point);
        generated_waypoints.push_back(t_wp);
    }
    Waypoint t_wp_final;
    Vector3D<double> elevated_landing_point=landing_point;
    elevated_landing_point.z=start_point.z;
    t_wp_final.position=elevated_landing_point;
    t_wp_final.yaw=0;
    generated_waypoints.push_back(t_wp_final);
    Waypoint t_wp_final_landed;
    t_wp_final_landed.position=landing_point;
    t_wp_final_landed.yaw=0;
    generated_waypoints.push_back(t_wp_final_landed);
    return generated_waypoints;
}

void navigator_ch3::addFireLocation(fire_id detected_fire_id, Vector3D<double> fire_location, Vector3D<double> fire_normal)
{
    Vector3D<double> t_fire_loc_at_corridor;
    Vector2D<double> t_fire_location;
    Vector2D<double> t_fire_normal;
    t_fire_location.x = fire_location.x;
    t_fire_location.y = fire_location.y;
    t_fire_normal.x = fire_normal.x;
    t_fire_normal.y = fire_normal.y;
    Line2D line_fire_normal;
    external_wall_fire_counter++;

    line_fire_normal.setPoint1(t_fire_location);
    line_fire_normal.setPoint2(t_fire_location + t_fire_normal);
    t_fire_loc_at_corridor.z = fire_location.z;
    line_fire_normal.scaleBy(dist_to_wall);
    t_fire_loc_at_corridor.x = line_fire_normal.getPoint2().x;
    t_fire_loc_at_corridor.y = line_fire_normal.getPoint2().y;
    fire_loc_at_corridor[(int)detected_fire_id] = t_fire_loc_at_corridor;
    fire_loc_at_building[(int)detected_fire_id]=fire_location;
    if (external_wall_fire_counter == 3)
    {
        if (MainMissionStateManager.getMissionState() == outdoor_navigation_states::AllGroundFiresDetected) {
            MainMissionStateManager.updateMissionState(outdoor_navigation_states::AllOutdoorFiresDetected);
        }
        else {
            MainMissionStateManager.updateMissionState(outdoor_navigation_states::AllWallFiresDetected);
        }
    }
}

double navigator_ch3::getDistanceToBuilding(Vector3D<double> t_point){
    Vector2D<double> t_point_2d;
    t_point_2d.x=t_point.x;
    t_point_2d.y=t_point.y;
    if (t_point.z>GF_FF_height){
        return Vector2D<double>::getL2Norm(SndF_outline.getClosestPoint(t_point_2d)-t_point_2d);
    }
    else{
        return Vector2D<double>::getL2Norm(GF_outline.getClosestPoint(t_point_2d)-t_point_2d);
    }
    return -1;
}

double navigator_ch3::getHeadingToPoint(Vector2D<double> base_point,Vector2D<double> target_point){
    Vector2D<double> t_diff=target_point-base_point;
    return atan2(t_diff.y,t_diff.x);
}
double navigator_ch3::getHeadingToPoint(Vector3D<double> base_point,Vector3D<double> target_point){
    Vector3D<double> t_diff=target_point-base_point;
    return atan2(t_diff.y,t_diff.x);
}