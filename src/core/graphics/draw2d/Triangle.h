#pragma once

#include <vector>

#include "math/Point2dInt.h"

struct Triangle
{
    std::vector<Point2dInt> vertices;

    Triangle();
    Triangle(std::vector<Point2dInt> vertices);
    Triangle(Point2dInt p1, Point2dInt p2, Point2dInt p3);
};