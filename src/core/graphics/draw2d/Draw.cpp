
#include <iostream>

#include "core/graphics/draw2d/Draw.h"

/*
void Draw::Line(SDL_Renderer *renderer, Point2d p1, Point2d p2)
{
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
}
*/

//  OK
void Draw::Line(SDL_Renderer *renderer, Point2dInt p1, Point2dInt p2)
{
    Point2dInt p0 = Point2dInt(p1);

    int dx = abs(p2.x - p1.x), sx = p1.x < p2.x ? 1 : -1;
    int dy = abs(p2.y - p1.y), sy = p1.y < p2.y ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    for (;;)
    {
        SDL_RenderDrawPoint(renderer, p0.x, p0.y);
        if (p0.x == p2.x && p0.y == p2.y)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            p0.x += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            p0.y += sy;
        }
    }
}

void Draw::PolygonWired(SDL_Renderer *renderer, std::vector<Point2dInt> points)
{
    if (points.size() < 3)
    {
        return;
    }

    for (int n = 0; n < points.size() - 1; n++)
    {
        Draw::Line(renderer, points[n], points[n + 1]);
    }
    Draw::Line(renderer, points[points.size() - 1], points[0]);
}
