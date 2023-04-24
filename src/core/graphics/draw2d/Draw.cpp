
#include <iostream>

#include "core/graphics/draw2d/Draw.h"

/*
void Draw::Line(SDL_Renderer *renderer, Point2d p1, Point2d p2)
{
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
}
*/

//  OK
void Draw::Line(SDL_Renderer *renderer, Point2d p1, Point2d p2)
{
    Point2d p0 = Point2d(p1);

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

/*
void Draw::Line(SDL_Renderer *renderer, Point2d p1, Point2d p2)
{

    int delta_x = (p2.x - p1.x);
    int delta_y = (p2.y - p1.y);

    int longest_side_length = (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);

    float x_inc = delta_x / (float)longest_side_length;
    float y_inc = delta_y / (float)longest_side_length;

    float current_x = p1.x;
    float current_y = p1.y;

    for (int i = 0; i <= longest_side_length; i++)
    {
        SDL_RenderDrawPoint(renderer, current_x, current_y);
        current_x += x_inc;
        current_y += y_inc;
    }
}
*/
/*
void Draw::Line(SDL_Renderer *renderer, Point2d p1, Point2d p2)
{
    int incy, incx; // Variables for amount of change in x and y

    int dy = p2.y - p1.y; // Calculate difference between y coordinates
    if (dy < 0)
    {              // If the line moves in the negative direction
        dy = -dy;  // ...get absolute value of difference
        incy = -1; // ...and set negative unit in y dimension
    }
    else
        incy = 1; // Else set positive unit in y dimension

    int dx = p2.x - p1.x; // Calculate difference between x coordinates
    if (dx < 0)
    {              // If the line moves in the negative direction
        dx = -dx;  // ...get absolute value of difference
        incx = -1; // ...and set negative unit in x dimension
    }
    else
        incx = 1; // Else set positive unit in y dimension

    Point2d p = Point2d(p1);

    int error_term = 0; // Initialize error term

    // If difference is bigger in x dimension prepare to count off in x direction
    if (dx > dy)
    {
        int length = dx + 1;

        // Loop through points  in x direction
        for (int i = 0; i < length; i++)
        {
            // Set the next pixel in the line to COLOR
            SDL_RenderDrawPoint(renderer, p.x, p.y);
            p.x += incx; // Move offset to next pixel in x direction
            error_term += dy;
            // Check to see if move required in y direction
            if (error_term > dx)
            {                     // If so...
                error_term -= dx; // ...reset error term
                p.y += incy;      // ...and move offset to next pixel in y dir.
            }
        }
    }
    else
    {
        // If difference is bigger in y dimension
        int length = dy + 1; // ...prepare to count off in y direction

        // Loop through points in y direction
        for (int i = 0; i < length; i++)
        {
            // Set the next pixel in the line to COLOR
            SDL_RenderDrawPoint(renderer, p.x, p.y);

            p.y += incy; // Move offset to next pixel in y direction

            error_term += dx; // Check to see if move required in x direction
            if (error_term > 0)
            {                     // If so...
                error_term -= dy; // ...reset error term
                p.x += incx;      // ...and move offset to next pixel in x dir.
            }
        }
    }
}
*/
void Draw::PolygonWired(SDL_Renderer *renderer, std::vector<Point2d> points)
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

/*

//  Sort points from top to bottom
std::vector<Point2d> sortedPoints = points;
std::sort(sortedPoints.begin(), sortedPoints.end(),
          [](const Point2d &lhs, const Point2d &rhs)
          {
              return lhs.y < rhs.y;
          });
    std::cout << "===================" << std::endl;
    for (Point2d point : sortedPoints)
    {
        std::cout << point.y << std::endl;
    }
*/

/*


void PixelGameEngine::DrawLine(const olc::vi2d& pos1, const olc::vi2d& pos2, Pixel p, uint32_t pattern)
    { DrawLine(pos1.x, pos1.y, pos2.x, pos2.y, p, pattern); }

    void PixelGameEngine::DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Pixel p, uint32_t pattern)
    {
        int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
        dx = x2 - x1; dy = y2 - y1;

        auto rol = [&](void) { pattern = (pattern << 1) | (pattern >> 31); return pattern & 1; };

        olc::vi2d p1(x1, y1), p2(x2, y2);
        //if (!ClipLineToScreen(p1, p2))
        //	return;
        x1 = p1.x; y1 = p1.y;
        x2 = p2.x; y2 = p2.y;

        // straight lines idea by gurkanctn
        if (dx == 0) // Line is vertical
        {
            if (y2 < y1) std::swap(y1, y2);
            for (y = y1; y <= y2; y++) if (rol()) Draw(x1, y, p);
            return;
        }

        if (dy == 0) // Line is horizontal
        {
            if (x2 < x1) std::swap(x1, x2);
            for (x = x1; x <= x2; x++) if (rol()) Draw(x, y1, p);
            return;
        }

        // Line is Funk-aye
        dx1 = abs(dx); dy1 = abs(dy);
        px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
        if (dy1 <= dx1)
        {
            if (dx >= 0)
            {
                x = x1; y = y1; xe = x2;
            }
            else
            {
                x = x2; y = y2; xe = x1;
            }

            if (rol()) Draw(x, y, p);

            for (i = 0; x < xe; i++)
            {
                x = x + 1;
                if (px < 0)
                    px = px + 2 * dy1;
                else
                {
                    if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
                    px = px + 2 * (dy1 - dx1);
                }
                if (rol()) Draw(x, y, p);
            }
        }
        else
        {
            if (dy >= 0)
            {
                x = x1; y = y1; ye = y2;
            }
            else
            {
                x = x2; y = y2; ye = y1;
            }

            if (rol()) Draw(x, y, p);

            for (i = 0; y < ye; i++)
            {
                y = y + 1;
                if (py <= 0)
                    py = py + 2 * dx1;
                else
                {
                    if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
                    py = py + 2 * (dx1 - dy1);
                }
                if (rol()) Draw(x, y, p);
            }
        }
    }

*/