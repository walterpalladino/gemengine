#include "core/graphics/draw2d/Triangle.h"

Triangle::Triangle()
{
}

Triangle::Triangle(std::vector<Point2dInt> vertices)
{
    if (vertices.size() == 3)
    {
        this->vertices = vertices;
    }
}

Triangle::Triangle(Point2dInt p1, Point2dInt p2, Point2dInt p3)
{
    this->vertices.push_back(p1);
    this->vertices.push_back(p2);
    this->vertices.push_back(p3);
}
