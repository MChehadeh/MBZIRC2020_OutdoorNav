#include "ROSUnit.hpp"

ROSUnit::ROSUnit(ros::NodeHandle& t_main_handler){

    _main_handler = t_main_handler;
}

ROSUnit::~ROSUnit() {

}

ros::NodeHandle ROSUnit::getNodeHandle(){

    return _main_handler;
}