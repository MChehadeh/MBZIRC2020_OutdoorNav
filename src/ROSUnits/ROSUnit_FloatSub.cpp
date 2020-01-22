#include "ROSUnit_FloatSub.hpp"

ROSUnit_FloatSub* ROSUnit_FloatSub::m_ptr[ROSUnit_capacity];
int ROSUnit_FloatSub::internal_counter=0;

void(*ROSUnit_FloatSub::callbackFunctionPointer[ROSUnit_capacity])(const std_msgs::Float32::ConstPtr& t_rec){
  ROSUnit_FloatSub::callback1,
  ROSUnit_FloatSub::callback2,
  ROSUnit_FloatSub::callback3,
  ROSUnit_FloatSub::callback4,
  ROSUnit_FloatSub::callback5
};

ROSUnit_FloatSub::ROSUnit_FloatSub(std::string t_name, ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler)
{
    m_sub = t_main_handler.subscribe(t_name, 1, ROSUnit_FloatSub::callbackFunctionPointer[internal_counter]);
    m_ptr[internal_counter] = this;
    internal_counter++;
}

ROSUnit_FloatSub::~ROSUnit_FloatSub()
{

}

void ROSUnit_FloatSub::callback1(const std_msgs::Float32::ConstPtr& t_rec)
{
    //Change the below code to match the message you want to emit
    FloatMsg t_msg;
    t_msg.data = t_rec->data;
    m_ptr[0]->emit_message((DataMessage*) &t_msg);
}

void ROSUnit_FloatSub::callback2(const std_msgs::Float32::ConstPtr& t_rec)
{
    //Change the below code to match the message you want to emit
    FloatMsg t_msg;
    t_msg.data = t_rec->data;
    m_ptr[1]->emit_message((DataMessage*) &t_msg);
}

void ROSUnit_FloatSub::callback3(const std_msgs::Float32::ConstPtr& t_rec)
{
    //Change the below code to match the message you want to emit
    FloatMsg t_msg;
    t_msg.data = t_rec->data;
    m_ptr[2]->emit_message((DataMessage*) &t_msg);
}

void ROSUnit_FloatSub::callback4(const std_msgs::Float32::ConstPtr& t_rec)
{
    //Change the below code to match the message you want to emit
    FloatMsg t_msg;
    t_msg.data = t_rec->data;
    m_ptr[3]->emit_message((DataMessage*) &t_msg);
}

void ROSUnit_FloatSub::callback5(const std_msgs::Float32::ConstPtr& t_rec)
{
    //Change the below code to match the message you want to emit
    FloatMsg t_msg;
    t_msg.data = t_rec->data;
    m_ptr[4]->emit_message((DataMessage*) &t_msg);
}