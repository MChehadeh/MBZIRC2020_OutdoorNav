#pragma once
#include "Vector2D.hpp"
#include "Line2D.hpp"
#include <vector>

enum class rect_sides {side1,side2};

class Rectangle {
    Line2D side1,side2;

public:
    double altitude=0; 
    Rectangle();
    ~Rectangle();
    //Point1 from side1 and side2 must match. Lines must be perpendicular. return true if successful
    bool updateRectangleSides(Line2D side1,Line2D side2); 
    Vector2D<double> getCenter();
    //Point1 from side1 and side2 is the fixed point.
    void scaleBy(double);
    void scaleBy(double scale_factor,rect_sides t_side_to_scale);
    void translateBy(Vector2D<double>);
    Vector2D<double> getClosestPoint(Vector2D<double> input_pt);
    bool checkPointIntersection(Vector2D<double>);
    std::vector<Vector2D<double>> generateClosedPathFromStartingPoint(Vector2D<double>);
    std::vector<Vector2D<double>> generatePathSegmentFromTwoPoint(Vector2D<double>,Vector2D<double>);
    Line2D getSide1();
    Line2D getSide2();
    Line2D getSide3();
    Line2D getSide4();
};

