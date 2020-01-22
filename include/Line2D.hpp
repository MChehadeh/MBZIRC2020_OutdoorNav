#pragma once
#include "Vector2D.hpp"
#include <algorithm>

const double min_sqr_dist_for_intersection=0.0001;

class Line2D{
private:
    Vector2D<double> point1;
    Vector2D<double> point2;
    Vector2D<double> diff;
public:
    void setPoint1(Vector2D<double>);
    void setPoint2(Vector2D<double>);
    Vector2D<double> getPoint1();
    Vector2D<double> getPoint2();
    Line2D();
    double getLength();
    double getAngle();
    Vector2D<double> getCenter();
    void scaleBy(double); //Point1 would be fixed
    void translateBy(Vector2D<double>);
    Vector2D<double> getClosestPoint(Vector2D<double>);
    bool checkPointIntesection(Vector2D<double>);
};
