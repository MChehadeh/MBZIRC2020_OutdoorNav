#include "ROSUnit_PointSub.hpp"

ROSUnit_PointSub* ROSUnit_PointSub::m_ptr[ROSUnit_capacity];
int ROSUnit_PointSub::internal_counter=0;

void(*ROSUnit_PointSub::callbackFunctionPointer[ROSUnit_capacity])(const geometry_msgs::Point::ConstPtr& t_rec){
  ROSUnit_PointSub::callback1,
  ROSUnit_PointSub::callback2,
  ROSUnit_PointSub::callback3,
  ROSUnit_PointSub::callback4,
  ROSUnit_PointSub::callback5
};

ROSUnit_PointSub::ROSUnit_PointSub(std::string t_name, ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler)
{
    m_sub = t_main_handler.subscribe(t_name, 1, ROSUnit_PointSub::callbackFunctionPointer[internal_counter]);
    m_ptr[internal_counter] = this;
    internal_counter++;
}

ROSUnit_PointSub::~ROSUnit_PointSub()
{

}

void ROSUnit_PointSub::callback1(const geometry_msgs::Point::ConstPtr& t_rec)
{
    //Change the below code to match the message you want to emit
    Vector3DMessage t_msg;
    Vector3D<float> t_vec;
    t_vec.x = t_rec->x;
    t_vec.y = t_rec->y;
    t_vec.z = t_rec->z;
    t_msg.setVector3DMessage(t_vec);
    m_ptr[0]->emit_message((DataMessage*) &t_msg);
}

void ROSUnit_PointSub::callback2(const geometry_msgs::Point::ConstPtr& t_rec)
{
    //Change the below code to match the message you want to emit
    Vector3DMessage t_msg;
    Vector3D<float> t_vec;
    t_vec.x = t_rec->x;
    t_vec.y = t_rec->y;
    t_vec.z = t_rec->z;
    t_msg.setVector3DMessage(t_vec);
    m_ptr[1]->emit_message((DataMessage*) &t_msg);
}

void ROSUnit_PointSub::callback3(const geometry_msgs::Point::ConstPtr& t_rec)
{
    //Change the below code to match the message you want to emit
    Vector3DMessage t_msg;
    Vector3D<float> t_vec;
    t_vec.x = t_rec->x;
    t_vec.y = t_rec->y;
    t_vec.z = t_rec->z;
    t_msg.setVector3DMessage(t_vec);
    m_ptr[2]->emit_message((DataMessage*) &t_msg);
}

void ROSUnit_PointSub::callback4(const geometry_msgs::Point::ConstPtr& t_rec)
{
    //Change the below code to match the message you want to emit
    Vector3DMessage t_msg;
    Vector3D<float> t_vec;
    t_vec.x = t_rec->x;
    t_vec.y = t_rec->y;
    t_vec.z = t_rec->z;
    t_msg.setVector3DMessage(t_vec);
    m_ptr[3]->emit_message((DataMessage*) &t_msg);
}

void ROSUnit_PointSub::callback5(const geometry_msgs::Point::ConstPtr& t_rec)
{
    //Change the below code to match the message you want to emit
    Vector3DMessage t_msg;
    Vector3D<float> t_vec;
    t_vec.x = t_rec->x;
    t_vec.y = t_rec->y;
    t_vec.z = t_rec->z;
    t_msg.setVector3DMessage(t_vec);
    m_ptr[4]->emit_message((DataMessage*) &t_msg);
}