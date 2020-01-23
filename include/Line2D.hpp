// Version: 3.0
// Author: Mohamad Chehadeh
// Date: 23 January 2020
// Release Note: Added check line intersection with a rectangle

#pragma once
#include "Vector2D.hpp"
#include <algorithm>

const double min_sqr_dist_for_intersection=0.0001;

class Line2D{
private:
    Vector2D<double> point1;
    Vector2D<double> point2;
    Vector2D<double> diff;
    static bool ccw(Vector2D<double> A,Vector2D<double> B,Vector2D<double> C); //Utility function for check_lines_intersection

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
    static bool check_lines_intersection(Line2D line1,Line2D line2);

};

    