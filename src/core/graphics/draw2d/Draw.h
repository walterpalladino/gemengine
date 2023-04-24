#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "math/Point2dInt.h"

class Draw
{
public:
    static void Line(SDL_Renderer *renderer, Point2dInt p1, Point2dInt p2);
    static void PolygonWired(SDL_Renderer *renderer, std::vector<Point2dInt> points);

    static void PolygonFilled(SDL_Renderer *renderer, std::vector<Point2dInt> points);
    static void TriangleFilled(SDL_Renderer *renderer, std::vector<Point2dInt> points);

private:
    static void GenerateScanlinesForEdge(Point2dInt p1, Point2dInt p2, std::vector<Point2dInt> *edges);
    static void RenderScanlines(SDL_Renderer *renderer, std::vector<Point2dInt> edges);
};
