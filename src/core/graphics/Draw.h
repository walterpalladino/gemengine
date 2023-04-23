#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "math/Point2d.h"

class Draw
{
public:
    static void Line(SDL_Renderer *renderer, Point2d p1, Point2d p2);
    static void PolygonWired(SDL_Renderer *renderer, std::vector<Point2d> points);
    static void PolygonFilled(SDL_Renderer *renderer, std::vector<Point2d> points);
};
