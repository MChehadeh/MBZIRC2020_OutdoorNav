#include "RotationMatrix3by3.hpp"
using namespace std;

RotationMatrix3by3::RotationMatrix3by3(/* args */){
}

RotationMatrix3by3::~RotationMatrix3by3(){
}

void RotationMatrix3by3::Update(Vector3D<double> t_input)
{ 
    Matrix3by3::v1.x =  cos(t_input.y)*cos(t_input.z);
    Matrix3by3::v1.y =  cos(t_input.x)*sin(t_input.z) - cos(t_input.z)*sin(t_input.x)*sin(t_input.y);
    Matrix3by3::v1.z = -cos(t_input.x)*cos(t_input.z)*sin(t_input.y) - sin(t_input.x)*sin(t_input.z);

    Matrix3by3::v2.x = -cos(t_input.y)*sin(t_input.z);
    Matrix3by3::v2.y =  cos(t_input.x)*cos(t_input.z) + sin(t_input.x)*sin(t_input.y)*sin(t_input.z);
    Matrix3by3::v2.z =  cos(t_input.x)*sin(t_input.y)*sin(t_input.z) - cos(t_input.z)*sin(t_input.x);

    Matrix3by3::v3.x =  sin(t_input.y);
    Matrix3by3::v3.y =  cos(t_input.y)*sin(t_input.x);
    Matrix3by3::v3.z =  cos(t_input.x)*cos(t_input.y);
}
