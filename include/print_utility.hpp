#pragma once

#include <vector>
#include <iostream>
#include "Vector2D.hpp"
#include "Vector3D.hpp"
#include "Line2D.hpp"
#include "Rectangle.hpp"
#include "Waypoint.hpp"
class print_utility{
public:
    static void print_vec_3d(std::vector<Vector3D<double>> lst_vec);

    static void print_vec_3d(Vector3D<double> lst_vec);

    static void print_vec_2d(std::vector<Vector2D<double>> lst_vec);

    static void print_vec_2d(Vector2D<double> lst_vec);

    static void print_vec_rect(std::vector<Rectangle> lst_rect);

    static void print_vec_rect(Rectangle lst_rect);

    static void print_vec_line(std::vector<Line2D> lst_line);

    static void print_vec_line(Line2D lst_line);

    static void print_waypoint(std::vector<Waypoint>);

    static void print_waypoint(Waypoint );
};
