#include "Matrix3by3.hpp"

Matrix3by3::Matrix3by3(){
}

Matrix3by3::Matrix3by3(Vector3D<double> t_v1, Vector3D<double> t_v2, Vector3D<double> t_v3)
{
    v1 = t_v1;
    v2 = t_v2;
    v3 = t_v3;
}

Vector3D<double> Matrix3by3::TransformVector(Vector3D<double> t_input)
{
    Vector3D<float> t_results;
    t_results.x = t_input.x*v1.x + t_input.y*v2.x + t_input.z*v3.x;
    t_results.y = t_input.x*v1.y + t_input.y*v2.y + t_input.z*v3.y;
    t_results.z = t_input.x*v1.z + t_input.y*v2.z + t_input.z*v3.z;
    return t_results;
}

void Matrix3by3::Transpose()
{
    Vector3D<double> t_aux;
    t_aux = v3;
    v3.x  = v1.z;
    v3.y  = v2.z;
    v1.z  = t_aux.x;
    v2.z  = t_aux.y;
    t_aux = v2;
    v2.x  = v1.y;
    v1.y  = t_aux.x;
}
