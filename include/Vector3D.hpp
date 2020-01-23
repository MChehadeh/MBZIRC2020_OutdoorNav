// Version: 1.1
// Author: Mohamad Chehadeh
// Date: 23 Jan 2020
// Minor Revision Note: Added conversion to Vector2D

#pragma once 
template  <class L> class Vector3D;

#include <cstdint>
#include "Vector2D.hpp"
template <class T>  

class Vector3D
{
        public:
        
                T x = 0;
                T y = 0;
                T z = 0;

                Vector3D<T> operator + (Vector3D<T> obj)
                {
                        Vector3D<T> res;
                        res.x = x + obj.x;
                        res.y = y + obj.y;
                        res.z = z + obj.z;
                        return res;
                }
                Vector3D<T> operator - (Vector3D<T> obj)
                {
                        Vector3D<T> res;
                        res.x = x - obj.x;
                        res.y = y - obj.y;
                        res.z = z - obj.z;
                        return res;
                }
                Vector3D<T> operator * (Vector3D<T> obj)
                {
                        Vector3D<T> res;
                        res.x = x * obj.x;
                        res.y = y * obj.y;
                        res.z = z * obj.z;
                        return res;
                }
                Vector3D<T> operator * (T tmp)
                {
                        Vector3D<T> res;
                        res.x = this->x * tmp;
                        res.y = this->y * tmp;
                        res.z = this->z * tmp;
                        return res;
                }
                Vector3D<T> operator / (T tmp)
                {
                        Vector3D<T> res;
                        res.x = this->x / tmp;
                        res.y = this->y / tmp;
                        res.z = this->z / tmp;
                        return res;
                }
                void operator = (T tmp)
                {
                        this->x = tmp;
                        this->y = tmp;
                        this->z = tmp;
                }

                template <typename M>
                operator Vector3D<M>()
                {
                        Vector3D<M> tmp;
                        tmp.x = M(this->x);
                        tmp.y = M(this->y);
                        tmp.z = M(this->z);

                        return tmp;
                }

                Vector2D<T> project_xy(){
                        Vector2D<T> res;
                        res.x=this->x;
                        res.y=this->y;
                        return res;
                }

};