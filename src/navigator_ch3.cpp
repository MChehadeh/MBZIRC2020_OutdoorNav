#include "navigator_ch3.hpp"
#define show_internals
using namespace std;

// TODO: Refactor to eliminate many repitions in the code
// VERY IMPORTANT! assumed tower and arena are parallel
navigator_ch3::navigator_ch3(){
}

void navigator_ch3::receive_msg_data(DataMessage* t_msg)
{
    if (t_msg->getType()==msg_type::FILTER_POINT){
        filterPointMsg* tmp = ((filterPointMsg*) t_msg);
        Vector3D<double> norm_vec;
        norm_vec = CollisionFinder::getNormalVector(tmp->side_of_hit);
        fire_id detected_fire_id = this->findFireID(tmp->filterPoint);
        #ifdef show_internals
        print_utility::print_vec_3d(norm_vec);
        #endif
        this->addFireLocation(detected_fire_id, tmp->filterPoint,norm_vec);
    }
    
}

void navigator_ch3::receive_msg_data(DataMessage* t_msg,int channel){
    if (channel==receiving_channels::UAV_Position){
        if(t_msg->getType() == msg_type::POSE)
        {
            latest_known_position.x = ((PoseMsg*)t_msg)->pose.x;
            latest_known_position.y = ((PoseMsg*)t_msg)->pose.y;
            latest_known_position.z = ((PoseMsg*)t_msg)->pose.z;
            //Find tip distance to wall
            Vector3D<double> nozzle_base_vector,nozzle_loc;
            nozzle_base_vector.x=nozzle_offset_to_center;
            // TODO Compensate for heading
            RotationMatrix3by3 rot_matrix;
            Vector3D<double> UAV_heading;
            UAV_heading.z=last_known_heading;
            rot_matrix.Update(UAV_heading);
            nozzle_loc=rot_matrix.TransformVector(nozzle_base_vector);
            nozzle_loc=nozzle_loc+latest_known_position;
            FloatMsg distance_to_wall_msg;
            distance_to_wall_msg.data=(float)this->getDistanceToBuilding(nozzle_loc);
            last_known_heading= ((PoseMsg*)t_msg)->pose.yaw;
            emit_message(&distance_to_wall_msg);
        }
    }
    else if (channel==receiving_channels::UAV_Orientation){
        if(t_msg->getType() == msg_type::POSE)
        {
            
        }
    }
    else if(channel==receiving_channels::Landing_Waypoints){
        if (t_msg->getType()==msg_type::EMPTY){
            std::vector<Waypoint> landing_path=this->generateWaypointsToLandingPoint(latest_known_position);
            PosesMsg t_wpts;
            for (int i=0;i<landing_path.size();i++){
                Pose t_wp_pose;
                t_wp_pose.x=landing_path[i].position.x;
                t_wp_pose.y=landing_path[i].position.y;
                t_wp_pose.z=landing_path[i].position.z;
                t_wp_pose.yaw=landing_path[i].yaw;
                t_wpts.p.poses.push_back(t_wp_pose);
            }
            #ifdef show_internals
            print_utility::print_waypoint(landing_path);
            #endif
            emit_message(&t_wpts);
        }
    }
    else if (channel==receiving_channels::Wall_Scanning_Waypoints){
        if (t_msg->getType()==msg_type::EMPTY){ //TODO: Refactor to reflect scan path request
            std::vector<Waypoint> scanning_path=this->generateWaypointsToCorridor(launch_point,scanning_corridors[0].altitude);
            std::vector<Waypoint> t_scanning_path_on_corridor=this->generateWaypointsForScanning((scanning_path.end()-1)->position);
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
            #ifdef show_internals
            print_utility::print_waypoint(scanning_path);
            #endif
            emit_message(&t_wpts);
        }
    }
    else if (channel==receiving_channels::Fire_Waypoints){
        if (t_msg->getType()==msg_type::INTEGER) //TODO: Refactor to reflect fire id path request
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
            #ifdef show_internals
            print_utility::print_waypoint(pathToFire);
            #endif
            emit_message(&t_wpts);
        }
    }
    else if (channel==receiving_channels::Ground_Scanning_Waypoints){
        if (t_msg->getType()==msg_type::EMPTY){
            std::vector<Waypoint> pathForGroundScanning=this->generateWaypointsForBlanketFireScanning(latest_known_position);
            PosesMsg t_wpts;
            for (int i=0;i<pathForGroundScanning.size();i++){
                Pose t_wp_pose;
                t_wp_pose.x=pathForGroundScanning[i].position.x;
                t_wp_pose.y=pathForGroundScanning[i].position.y;
                t_wp_pose.z=pathForGroundScanning[i].position.z;
                t_wp_pose.yaw=pathForGroundScanning[i].yaw;
                t_wpts.p.poses.push_back(t_wp_pose);
            }
            #ifdef show_internals
            print_utility::print_waypoint(pathForGroundScanning);
            #endif
            emit_message(&t_wpts);
        }
    }
    

}

navigator_ch3::navigator_ch3(Rectangle t_GF, Rectangle t_SndF, double t_altitude_increment, double t_min_dist_to_floor,
double t_max_altitude, double t_dist_to_wall, double t_GF_FF_height, double t_GF_height)
{
    //Initialize variables
    Vector3D<double> null_vec;
    for (int i=0; i<=(int)last_fire_id; i++){
        fire_loc_at_corridor.push_back(null_vec);
        fire_loc_at_building.push_back(null_vec);
    }
    GF_outline=t_GF;
    SndF_outline=t_SndF;
    GF_height = t_GF_height;
    GF_FF_height = t_GF_FF_height;
    dist_to_wall=t_dist_to_wall;
    min_dist_to_floor=t_min_dist_to_floor;
    altitude_increment=t_altitude_increment;
    max_altitude=t_max_altitude;
    //Generate scanning waypoints
    Rectangle base_corridor_gf;
    base_corridor_gf = t_GF;

    base_corridor_gf.scaleBy((t_dist_to_wall*2+t_GF.getSide1().getLength())/t_GF.getSide1().getLength(),rect_sides::side1);
    base_corridor_gf.scaleBy((t_dist_to_wall*2+t_GF.getSide2().getLength())/t_GF.getSide2().getLength(),rect_sides::side2);
    Vector2D<double> offset_floor_outline;
    offset_floor_outline = t_GF.getCenter() - base_corridor_gf.getCenter();
    base_corridor_gf.translateBy(offset_floor_outline);
    Rectangle base_corridor_sndf;
    base_corridor_sndf = t_SndF;
    base_corridor_sndf.scaleBy((t_dist_to_wall*2+t_SndF.getSide1().getLength())/t_SndF.getSide1().getLength(),rect_sides::side1);
    base_corridor_sndf.scaleBy((t_dist_to_wall*2+t_SndF.getSide2().getLength())/t_SndF.getSide2().getLength(),rect_sides::side2);
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
        #ifdef show_internals
        //print_utility::print_vec_3d(start_point);
        //print_utility::print_vec_2d(res_path);
        #endif
        for (int j=0; j<res_path.size(); j++){
            Waypoint t_wp;
            t_wp.position.x = res_path[j].x;
            t_wp.position.y = res_path[j].y;
            t_wp.position.z = scanning_corridors[i].altitude;
            t_wp.yaw=getHeadingToPoint(res_path[j],scanning_corridors[i].getCenter());
            t_generated_waypoints.push_back(t_wp);
        }
    }
    #ifdef show_internals

    //print_utility::print_vec_rect(scanning_corridors);
    //print_utility::print_waypoint(t_generated_waypoints);
    #endif
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

//TODO Note: This generates waypoints to the first corridor
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
    Vector2D<double> start_point_2d;
    start_point_2d.x=start_point.x;
    start_point_2d.y=start_point.y;
    Vector2D<double> landing_point_2d;
    landing_point_2d.x=landing_point.x;
    landing_point_2d.y=landing_point.y;
    Line2D line_from_start_to_land;
    line_from_start_to_land.setPoint1(start_point_2d);
    line_from_start_to_land.setPoint2(landing_point_2d);
    
    Rectangle used_floor_outline;
    if (start_point.z>this->GF_FF_height+min_dist_to_floor){
        used_floor_outline=SndF_outline;

    }
    else{
        used_floor_outline=GF_outline;
    }
    Rectangle used_corridor;
    used_corridor = used_floor_outline;
    used_corridor.altitude=start_point.z;

    used_corridor.scaleBy((dist_to_wall*2+used_floor_outline.getSide1().getLength())/used_floor_outline.getSide1().getLength(),rect_sides::side1);
    used_corridor.scaleBy((dist_to_wall*2+used_floor_outline.getSide2().getLength())/used_floor_outline.getSide2().getLength(),rect_sides::side2);
    Vector2D<double> offset_floor_outline;
    offset_floor_outline = used_floor_outline.getCenter() - used_corridor.getCenter();
    used_corridor.translateBy(offset_floor_outline);
    #ifdef show_internals
    print_utility::print_vec_rect(used_corridor);
    print_utility::print_vec_line(line_from_start_to_land);
    #endif
    if (used_corridor.checkLineIntersection(line_from_start_to_land)){
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
    #ifdef show_internals
    print_utility::print_vec_line(line_fire_normal);
    #endif
    line_fire_normal.scaleBy(dist_to_wall);
    t_fire_loc_at_corridor.x = line_fire_normal.getPoint2().x;
    t_fire_loc_at_corridor.y = line_fire_normal.getPoint2().y;
    t_fire_loc_at_corridor.z = fire_location.z;
    #ifdef show_internals
    print_utility::print_vec_3d(t_fire_loc_at_corridor);
    print_utility::print_vec_line(line_fire_normal);
    #endif
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

void navigator_ch3::updateBlanketFireParameters(Rectangle area_outline_para,double blanket_fire_scanning_altitude_para,double blanket_fire_dist_to_perimeter_para,double blanket_fire_side_step_size_para){
    blanket_fire_scanning_altitude=blanket_fire_scanning_altitude_para;
    blanket_fire_dist_to_perimeter=blanket_fire_dist_to_perimeter_para;
    blanket_fire_side_step_size=blanket_fire_side_step_size_para;
    area_outline=area_outline_para;

    //Generate scanning path outline
    scanning_path_outline = area_outline;

    scanning_path_outline.scaleBy((-blanket_fire_dist_to_perimeter*2+area_outline.getSide1().getLength())/area_outline.getSide1().getLength(),rect_sides::side1);
    scanning_path_outline.scaleBy((-blanket_fire_dist_to_perimeter*2+area_outline.getSide2().getLength())/area_outline.getSide2().getLength(),rect_sides::side2);
    Vector2D<double> offset_scanning_outline;
    offset_scanning_outline = area_outline.getCenter() - scanning_path_outline.getCenter();
    scanning_path_outline.translateBy(offset_scanning_outline);

    

}

std::vector<Waypoint> navigator_ch3::generateWaypointsForBlanketFireScanning(Vector3D<double> start_point){
    std::vector<Waypoint> generated_waypoints;
    // Find the no pass corridor
    Rectangle no_pass_corridor;
    no_pass_corridor = GF_outline;
    no_pass_corridor.scaleBy((dist_to_wall*2+GF_outline.getSide1().getLength())/GF_outline.getSide1().getLength(),rect_sides::side1);
    no_pass_corridor.scaleBy((dist_to_wall*2+GF_outline.getSide2().getLength())/GF_outline.getSide2().getLength(),rect_sides::side2);
    Vector2D<double> offset_floor_outline;
    offset_floor_outline = GF_outline.getCenter() - no_pass_corridor.getCenter();
    no_pass_corridor.translateBy(offset_floor_outline);
    //Generate first WP for altitude adjustment
    Vector3D<double> start_point_alt_adj=start_point;
    start_point_alt_adj.z=blanket_fire_scanning_altitude;
    Waypoint t_wp_start_point_alt_adj;
    t_wp_start_point_alt_adj.position=start_point_alt_adj;
    t_wp_start_point_alt_adj.yaw=last_known_heading;
    generated_waypoints.push_back(t_wp_start_point_alt_adj);
    //Get to the first point in scanning path avoiding obstacles
    Vector3D<double> first_scanning_point;
    first_scanning_point.x=scanning_path_outline.getSide1().getPoint1().x;
    first_scanning_point.y=scanning_path_outline.getSide1().getPoint1().y;
    first_scanning_point.z=blanket_fire_scanning_altitude;
    Vector2D<double> first_scanning_point_2d;
    first_scanning_point_2d.x=first_scanning_point.x;
    first_scanning_point_2d.y=first_scanning_point.y;

    Vector2D<double> start_point_2d;
    start_point_2d.x=start_point.x;
    start_point_2d.y=start_point.y;
    Line2D line_start_to_scanning_path;
    line_start_to_scanning_path.setPoint1(start_point_2d);
    line_start_to_scanning_path.setPoint2(first_scanning_point_2d);

    if (no_pass_corridor.checkLineIntersection(line_start_to_scanning_path)){
        Vector2D<double> start_point_on_corridor_2d=no_pass_corridor.getClosestPoint(start_point_2d);
        Vector2D<double> end_point_on_corridor_2d=no_pass_corridor.getClosestPoint(first_scanning_point_2d);
        std::vector<Vector2D<double>> path_on_corridor= no_pass_corridor.generatePathSegmentFromTwoPoint(start_point_on_corridor_2d,end_point_on_corridor_2d);
        
        for (int i=0;i<path_on_corridor.size();i++){
            Waypoint t_wp;
            Vector3D<double> t_pos_wp;
            t_pos_wp.x=path_on_corridor[i].x;
            t_pos_wp.y=path_on_corridor[i].y;
            t_pos_wp.z=start_point.z;
            t_wp.position=t_pos_wp;
            t_wp.yaw=getHeadingToPoint(path_on_corridor[i],first_scanning_point_2d);
            generated_waypoints.push_back(t_wp);
        }
    }
    Waypoint t_wp_first_scanning_point;
    t_wp_first_scanning_point.position=first_scanning_point;
    t_wp_first_scanning_point.yaw=blanket_scanning_yaw;
    generated_waypoints.push_back(t_wp_first_scanning_point);
    //Generate zig-zag scanning path
    Vector2D<double> side_shift_operator;
    side_shift_operator=(scanning_path_outline.getSide1().getPoint2()-scanning_path_outline.getSide1().getPoint1())/(Vector2D<double>::getL2Norm(scanning_path_outline.getSide1().getPoint2()-scanning_path_outline.getSide1().getPoint1()));
    side_shift_operator=side_shift_operator*blanket_fire_side_step_size;
    Line2D scan_vertical_line=scanning_path_outline.getSide2();
    bool vertical_line_sample_point1_first=true;
    scan_vertical_line.translateBy(side_shift_operator*-1.);
    do {
        scan_vertical_line.translateBy(side_shift_operator);
        Vector3D<double> p1=scan_vertical_line.getPoint1().convertTo3D(blanket_fire_scanning_altitude);
        Vector3D<double> p2=scan_vertical_line.getPoint2().convertTo3D(blanket_fire_scanning_altitude);
        Waypoint t_wp_1,t_wp_2;
        t_wp_1.yaw=blanket_scanning_yaw;
        t_wp_2.yaw=blanket_scanning_yaw;
        if (vertical_line_sample_point1_first){
            t_wp_1.position=p1;
            t_wp_2.position=p2;
        }
        else{
            t_wp_1.position=p2;
            t_wp_2.position=p1;
        }
        vertical_line_sample_point1_first=!vertical_line_sample_point1_first;
        generated_waypoints.push_back(t_wp_1);
        generated_waypoints.push_back(t_wp_2);
    } 
    while (Vector2D<double>::getL2Norm(scan_vertical_line.getPoint1(),scanning_path_outline.getSide1().getPoint2())>Vector2D<double>::getL2Norm(side_shift_operator));
    return generated_waypoints;
}