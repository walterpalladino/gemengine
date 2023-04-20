
#include "core/graphics/Draw.h"

void Draw::Line(SDL_Renderer *renderer, Point2d p1, Point2d p2)
{
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
}
