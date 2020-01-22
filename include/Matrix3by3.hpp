#pragma once
#include "Vector3D.hpp"

class Matrix3by3
{
    protected:
    Vector3D<double> v1, v2, v3;
    public:
    Matrix3by3();
    Matrix3by3(Vector3D<double>, Vector3D<double>, Vector3D<double>);
    Vector3D<double> TransformVector(Vector3D<double>);
    void Transpose();
};
