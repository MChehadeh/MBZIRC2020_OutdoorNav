#pragma once
#include "Matrix3by3.hpp"
#include "Vector3D.hpp"
#include <iostream>
#include <math.h>

class RotationMatrix3by3 : public Matrix3by3
{
    private:
        /* data */
    public:
        RotationMatrix3by3(/* args */);
        ~RotationMatrix3by3();
        void Update(Vector3D<float>);
};

