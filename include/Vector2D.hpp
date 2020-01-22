// Version: 2.0
// Author: Mohamad Chehadeh
// Date: 30 Dec 2019
//Revision Note: Added static operations on vectors
#pragma once 

#include <cstdint>
#include <math.h>
template <class T>  

class Vector2D
{
        public:
        
                T x = 0;
                T y = 0;

                Vector2D<T> operator + (Vector2D<T> obj)
                {
                        Vector2D<T> res;
                        res.x = x + obj.x;
                        res.y = y + obj.y;
                        return res;
                }
                Vector2D<T> operator - (Vector2D<T> obj)
                {
                        Vector2D<T> res;
                        res.x = x - obj.x;
                        res.y = y - obj.y;
                        return res;
                }
                Vector2D<T> operator * (Vector2D<T> obj)
                {
                        Vector2D<T> res;
                        res.x = x * obj.x;
                        res.y = y * obj.y;
                        return res;
                }
                Vector2D<T> operator * (T tmp)
                {
                        Vector2D<T> res;
                        res.x = this->x * tmp;
                        res.y = this->y * tmp;
                        return res;
                }
                Vector2D<T> operator / (T tmp)
                {
                        Vector2D<T> res;
                        res.x = this->x / tmp;
                        res.y = this->y / tmp;
                        return res;
                }
                void operator = (T tmp)
                {
                        this->x = tmp;
                        this->y = tmp;
                }

                template <typename M>
                operator Vector2D<M>()
                {
                        Vector2D<M> tmp;
                        tmp.x = M(this->x);
                        tmp.y = M(this->y);
                        return tmp;
                }

                static double getL2Norm(Vector2D<T> vec1,Vector2D<T> vec2){
                    Vector2D<T> diff_vec=vec2-vec1;
                    return sqrt(diff_vec.x*diff_vec.x+diff_vec.y*diff_vec.y);
                }
                static double getDirection(Vector2D<T> vec1){
                    return atan2(vec1.y,vec1.x);
                }
                static double getL2Norm(Vector2D<T> vec1){
                    return sqrt(vec1.x*vec1.x+vec1.y*vec1.y);
                }
                static double getL2NormSquared(Vector2D<T> vec1){
                    return vec1.x*vec1.x+vec1.y*vec1.y;
                }
                static Vector2D<T> normalize(Vector2D<T> vec1){
                    return vec1/getL2Norm(vec1);
                }
                static double dotProduct(Vector2D<T> vec1,Vector2D<T> vec2){
                        return vec1.x*vec2.x+vec1.y*vec2.y;
                }

};