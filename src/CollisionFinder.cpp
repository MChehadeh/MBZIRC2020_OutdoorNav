#include "CollisionFinder.hpp"

// Vector3D<float> CollisionFinder::getNormalVector(Vector3D<float> world_normal, building_sides& hit_side);
// Vector3D<float> CollisionFinder::getNormalVector(building_sides hit_side);

CollisionFinder::CollisionFinder(Rectangle t_GF_outline, Rectangle t_SndF_outline, double GF_FF_height, double SndF_height)
{
    // Create the collision world
    rp3d::CollisionWorld world;
    
    // Initial position and orientation of the rigid body
    rp3d::Vector3 initPosition (0.0, 0.0, 0.0) ;
    rp3d::Quaternion initOrientation = rp3d::Quaternion::identity();
    rp3d::Transform unit_transform(initPosition, initOrientation);
    
    // Create a rigid body in the world
    rp3d::CollisionBody* Building_GF_FstF_Body;
    rp3d::CollisionBody* Building_SndF_Body;
    Building_GF_FstF_Body = world.createCollisionBody(unit_transform);
    Building_SndF_Body = world.createCollisionBody(unit_transform);
    
    //Defining the halfExtents for both buildings
    Vector3D<double> halfExtents_GF_FstF_Cube,halfExtents_SndF_Cube;
    halfExtents_GF_FstF_Cube.x = t_GF_outline.getSide1().getLength()/2.;
    halfExtents_GF_FstF_Cube.y = t_GF_outline.getSide2().getLength()/2.;
    halfExtents_GF_FstF_Cube.z = GF_FF_height/2.;
    
    halfExtents_SndF_Cube.x = t_SndF_outline.getSide1().getLength()/2.;
    halfExtents_SndF_Cube.y = t_SndF_outline.getSide2().getLength()/2.;
    halfExtents_SndF_Cube.z = (SndF_height-GF_FF_height)/2.;
    /* Made for testing only */
    // Transform to the required position in the world
    // rp3d::Vector3 NewPosition (-0.1, 2.7, 0.0) ;
    // rp3d::Quaternion NewOrientation = rp3d::Quaternion::identity();
    // rp3d::Transform Newtransform(NewPosition, NewOrientation);
    // body->setTransform(Newtransform);
    /* Made for testing only */

    // Transform to the required position in the world
    // Set the center of building1 on 5 x-axis, 5 y-axis, 0.5 z-axis, 0.5 is suitable so that the ground plane of the building will be on the z=0 plane.
    // Set building2 besides building1
    rp3d::Vector3 PositionBuilding_GF_FstF (t_GF_outline.getSide1().getPoint1().x+halfExtents_GF_FstF_Cube.x, 
        t_GF_outline.getSide1().getPoint1().y+halfExtents_GF_FstF_Cube.y, halfExtents_GF_FstF_Cube.z);
    rp3d::Vector3 PositionBuilding_SndF (t_SndF_outline.getSide1().getPoint1().x+halfExtents_SndF_Cube.x, 
        t_SndF_outline.getSide1().getPoint1().y+halfExtents_SndF_Cube.y,halfExtents_SndF_Cube.z+GF_FF_height);
    rp3d::Quaternion OrientationBuildings = rp3d::Quaternion::identity();
    rp3d::Transform transformBuilding1(PositionBuilding_GF_FstF, OrientationBuildings);
    rp3d::Transform transformBuilding2(PositionBuilding_SndF, OrientationBuildings);
    
    // Apply the transformation to the desired place
    Building_GF_FstF_Body->setTransform(transformBuilding1);
    Building_SndF_Body->setTransform(transformBuilding2);

    // Rigid body dimensions 
    rp3d::Vector3 buildingHalfExtents_GF_FstF(halfExtents_GF_FstF_Cube.x, halfExtents_GF_FstF_Cube.y, halfExtents_GF_FstF_Cube.z);
    rp3d::Vector3 buildingHalfExtents_SndF(halfExtents_SndF_Cube.x, halfExtents_SndF_Cube.y, halfExtents_SndF_Cube.z);
    const rp3d::BoxShape Cube_GF_FstF(buildingHalfExtents_GF_FstF);
    const rp3d::BoxShape Cube_SndF(buildingHalfExtents_SndF);
    building_GF_FstF = Building_GF_FstF_Body->addCollisionShape((rp3d::CollisionShape*) &Cube_GF_FstF, unit_transform);
    building_SndF = Building_SndF_Body->addCollisionShape((rp3d::CollisionShape*) &Cube_SndF, unit_transform);
}

CollisionFinder::~CollisionFinder(){
}
//Important note about the model: side1 must align with inertial x-axis
Vector3D<float> CollisionFinder::getNormalVector(building_sides hit_side)
{
    Vector3D<float> t_res;
    switch (hit_side)
    {
        case building_sides::side1 :
            t_res.x = 0; t_res.y = -1; t_res.z = 0;
            break;
        case building_sides::side2 :
            t_res.x = -1; t_res.y = 0; t_res.z = 0;
            break;
        case building_sides::side3 :
            t_res.x = 0; t_res.y = 1; t_res.z = 0;
            break;
        case building_sides::side4 :
            t_res.x = 1; t_res.y = 0; t_res.z = 0;  
            break;   
        default:
            break;
    }
    return t_res;
}

Vector3D<float> CollisionFinder::getNormalVector(Vector3D<float> world_normal, building_sides& side_of_hit)
{
    Vector3D<float> t_res;
    if (abs(world_normal.y - 1)<0.0001) {
        side_of_hit = building_sides::side1;
        }
    else if (abs(world_normal.y + 1)<0.0001){
        side_of_hit = building_sides::side2;     
        }
    else if (abs(world_normal.x - 1)<0.0001) {
        side_of_hit = building_sides::side3;      
        }
    else if (abs(world_normal.x + 1)<0.0001) {
        side_of_hit = building_sides::side4;     
    }
    t_res = CollisionFinder::getNormalVector(side_of_hit);
    return t_res;
}

void CollisionFinder::receive_msg_data(DataMessage* t_msg)
{
    if (t_msg->getType() == msg_type::VECTOR)
    {
        std::cout << "inside receive data CollisionFinder" << std::endl;
        VectorMsg* t_fireline = ((VectorMsg*) t_msg);
        Vector3D<float> t_p1, t_p2;
        t_p1 = t_fireline->p1;
        t_p2 = t_fireline->p2;
        std::cout << "inside receive data CollisionFinder 1" << std::endl;
        FindCollisionData(t_p1, t_p2);
        std::cout << "inside receive data CollisionFinder 2" << std::endl;
    }
}

void CollisionFinder::FindCollisionData(Vector3D<float> t_p1, Vector3D<float> t_p2)
{
    // Create the ray
    std::cout << "inside receive data CollisionFinder 1.1" << std::endl;
    rp3d::Vector3 startPoint(t_p1.x , t_p1.y, t_p1.z);
    rp3d::Vector3 endPoint(1000*t_p2.x , 1000*t_p2.y, 1000*t_p2.z);
    rp3d::Ray my_ray(startPoint, endPoint);

    // Create the geometry vectors
    Vector3D<float> P1, P2, P3;

    // Create the raycast info object for the raycast result
    rp3d::RaycastInfo raycastInfo;
    std::cout << "inside receive data CollisionFinder 1.2" << std::endl;
    // Raycast test, if (Hit Angle < 30), accept the collision
    if (building_GF_FstF->raycast(my_ray, raycastInfo)) 
    {   
        // std::cout << raycastInfo.worldPoint.length() << std::endl;
        // std::cout << raycastInfo.hitFraction << std::endl;
        // std::cout << raycastInfo.body->getTransform().getPosition().x << std::endl;
        // std::cout << raycastInfo.body->getTransform().getPosition().y << std::endl;
        // std::cout << raycastInfo.body->getTransform().getPosition().z << std::endl;
        std::cout << "inside receive data CollisionFinder 1.2.1" << std::endl;
        Vector3D<float> NorVec;
        building_sides hit_side;
        NorVec.x = raycastInfo.worldNormal.x;
        NorVec.y = raycastInfo.worldNormal.y;
        NorVec.z = raycastInfo.worldNormal.z;
        NorVec = getNormalVector(NorVec, hit_side);
        P1.x = startPoint.x; P1.y = startPoint.y; P1.z = startPoint.z;
        P2.x = raycastInfo.worldPoint.x; P2.y = raycastInfo.worldPoint.y; P2.z = raycastInfo.worldPoint.z;
        P3.x = NorVec.x + raycastInfo.worldPoint.x; P3.y = NorVec.y + raycastInfo.worldPoint.y; P3.z = NorVec.z + raycastInfo.worldPoint.z;
        // Create the vectors from points
        Vector3D<float> NewPoint1 = P2-P1;
        Vector3D<float> NewPoint2 = P2-P3;
        // We are using cos x = A.B/|A|x|B|, where A.B is the dot product of vector A, and B, |A| or |B| is the magnitude.
        float DotProduct = NewPoint1.x*NewPoint2.x + NewPoint1.y*NewPoint2.y + NewPoint1.z*NewPoint2.z;
        float Mag_NewPoint1 = sqrt(pow(NewPoint1.x,2) + pow(NewPoint1.y,2) + pow(NewPoint1.z,2));
        float Mag_NewPoint2 = sqrt(pow(NewPoint2.x,2) + pow(NewPoint2.y,2) + pow(NewPoint2.z,2));
        // Calculate the angle
        float AngleOfHit = (180/M_PI)*acos(DotProduct/(Mag_NewPoint1*Mag_NewPoint2));
        std::cout<<"Angle of Fire: "<< AngleOfHit <<std::endl;
        std::cout << "inside receive data CollisionFinder 1.2.2" << std::endl;
        if (AngleOfHit < 30)
        {
            std::cout << "inside receive data CollisionFinder 1.2.2.1" << std::endl;
            // Announce the confirmed hit
            std::cout<<"Fire Detected on Building 1: "
                                <<raycastInfo.worldPoint.x <<" "
                                <<raycastInfo.worldPoint.y <<" "
                                <<raycastInfo.worldPoint.z <<std::endl;
            std::cout<<"Plane X: "<< raycastInfo.worldNormal.x <<std::endl;
            std::cout<<"Plane Y: "<< raycastInfo.worldNormal.y <<std::endl;
            // Emit the hit point to the filter
            Vector3D<float> building1HitPoint;
            building1HitPoint.x = raycastInfo.worldPoint.x;
            building1HitPoint.y = raycastInfo.worldPoint.y;
            building1HitPoint.z = raycastInfo.worldPoint.z;
            
            filterPointMsg HitPointTofilter;
            HitPointTofilter.setFilterMessage(building1HitPoint);
            HitPointTofilter.side_of_hit = hit_side;
            std::cout << "inside receive data CollisionFinder 1.2.2.2" << std::endl;
            this->emit_message((DataMessage*) &HitPointTofilter);
        }
        else {
            std::cout<<"Angle not suitable. No Fire Detected"<<std::endl;
        }        
    }
    else if (building_SndF->raycast(my_ray, raycastInfo)) 
    {
        std::cout << "inside receive data CollisionFinder 1.2.3" << std::endl;
        Vector3D<float> NorVec;
        building_sides hit_side;
        NorVec.x = raycastInfo.worldNormal.x;
        NorVec.y = raycastInfo.worldNormal.y;
        NorVec.z = raycastInfo.worldNormal.z;
        NorVec = getNormalVector(NorVec, hit_side);
        P1.x = startPoint.x; P1.y = startPoint.y; P1.z = startPoint.z;
        P2.x = raycastInfo.worldPoint.x; P2.y = raycastInfo.worldPoint.y; P2.z = raycastInfo.worldPoint.z;
        P3.x = NorVec.x + raycastInfo.worldPoint.x; P3.y = NorVec.y + raycastInfo.worldPoint.y; P3.z = NorVec.z + raycastInfo.worldPoint.z;
        // Create the vectors from points
        Vector3D<float> NewPoint1 = P2-P1;
        Vector3D<float> NewPoint2 = P2-P3;
        // We are using cos(x) = A.B/|A|x|B|, where A.B is the dot product of vector A, and B, |A| or |B| is the magnitude.
        float DotProduct = NewPoint1.x*NewPoint2.x + NewPoint1.y*NewPoint2.y + NewPoint1.z*NewPoint2.z;
        float Mag_NewPoint1 = sqrt(pow(NewPoint1.x,2) + pow(NewPoint1.y,2) + pow(NewPoint1.z,2));
        float Mag_NewPoint2 = sqrt(pow(NewPoint2.x,2) + pow(NewPoint2.y,2) + pow(NewPoint2.z,2));
        // Calculate the angle
        float AngleOfHit = (180/M_PI)*acos(DotProduct/(Mag_NewPoint1*Mag_NewPoint2));
        std::cout<<"Angle of Hit: "<<AngleOfHit<<std::endl;
        std::cout << "inside receive data CollisionFinder 1.2.3.1" << std::endl;
        if (AngleOfHit < 30)
        {
            // Announce the confirmed hit
            std::cout<<"Fire Detected on Building 2: " 
                                <<raycastInfo.worldPoint.x <<" "
                                <<raycastInfo.worldPoint.y <<" "
                                <<raycastInfo.worldPoint.z <<std::endl;
            std::cout<<"Plane X: "<< raycastInfo.worldNormal.x <<std::endl;
            std::cout<<"Plane Y: "<< raycastInfo.worldNormal.y <<std::endl;
            // Emit the hit point to the filter
            Vector3D<float> building2HitPoint;
            building2HitPoint.x = raycastInfo.worldPoint.x;
            building2HitPoint.y = raycastInfo.worldPoint.y;
            building2HitPoint.z = raycastInfo.worldPoint.z;

            filterPointMsg HitPointTofilter;
            HitPointTofilter.setFilterMessage(building2HitPoint);
            HitPointTofilter.side_of_hit = hit_side;
            this->emit_message((DataMessage*) &HitPointTofilter);
        }
        else {
            std::cout<<"Angle not suitable. No Fire Detected"<<std::endl;
        }
    }
    else {
        std::cout<< "Fire NOT Detected!" <<std::endl;
    }
    std::cout << "inside receive data CollisionFinder 1.2.4" << std::endl;
}