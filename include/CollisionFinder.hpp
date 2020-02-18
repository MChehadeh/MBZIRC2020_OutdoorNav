#pragma once
#include "iostream"
#include "VectorMsg.hpp"
#include "Vector3DMessage.hpp"
#include "MsgEmitter.hpp"
#include "MsgReceiver.hpp"
#include "time.h"
#include "ros/ros.h"
#include "filterPointMsg.hpp"
#include "reactphysics3d.h"     // collision library
#include "Rectangle.hpp"
#include "Line2D.hpp"
//using namespace reactphysics3d; // collision library

class CollisionFinder : public msg_emitter, public msg_receiver {

private:
    void receive_msg_data(DataMessage* t_msg);
    void FindCollisionData(Vector3D<float>, Vector3D<float>);
    rp3d::ProxyShape* building_GF_FstF;
    rp3d::ProxyShape* building_SndF;
    rp3d::CollisionBody* Building_GF_FstF_Body;
    rp3d::CollisionBody* Building_SndF_Body;
    rp3d::CollisionWorld world;
    rp3d::BoxShape* Cube_GF_FstF;
    rp3d::BoxShape* Cube_SndF;
public:
    // Important note about the model: side1 must align with inertial x-axis
    static Vector3D<float> getNormalVector(Vector3D<float> world_normal, building_sides& hit_side);
    static Vector3D<float> getNormalVector(building_sides hit_side);
    CollisionFinder(Rectangle t_GF_outline, Rectangle t_SndF_outline, double GF_FF_height, double SndF_height);
    ~CollisionFinder();
};