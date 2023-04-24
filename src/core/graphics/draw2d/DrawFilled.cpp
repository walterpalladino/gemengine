#include <iostream>

#include "core/graphics/draw2d/Draw.h"

void Draw::PolygonFilled(SDL_Renderer *renderer, std::vector<Point2d> points)
{

    int ydiff1, ydiff2,         // Difference between starting x and ending x
        xdiff1, xdiff2,         // Difference between starting y and ending y
        start,                  // Starting offset of line between edges
        length,                 // Distance from edge 1 to edge 2
        errorterm1, errorterm2, // Error terms for edges 1 & 2
        count1, count2,         // Increment count for edges 1 & 2
        xunit1, xunit2;         // Unit to advance x offset for edges 1 & 2

    // Initialize count of number of edges drawn:
    int edgecount = points.size() - 1;

    // Determine which vertex is at top of polygon:
    int firstvert = 0;         // Start by assuming vertex 0 is at top
    int min_amt = points[0].y; // Find y coordinate of vertex 0
    for (int i = 1; i < points.size(); i++)
    { // Search thru vertices
        if ((points[i].y) < min_amt)
        {                  // Is another vertex higher?
            firstvert = i; // If so, replace previous top vertex
            min_amt = points[i].y;
        }
    }

    // Finding starting and ending vertices of first two edges:
    int startvert1 = firstvert; // Get starting vertex of edge 1
    int startvert2 = firstvert; // Get starting vertex of edge 2

    int xstart1 = points[startvert1].x;
    int ystart1 = points[startvert1].y;
    int xstart2 = points[startvert2].x;
    int ystart2 = points[startvert2].y;

    // Get ending vertex of edge 1
    int endvert1 = startvert1 - 1;
    if (endvert1 < 0)
        endvert1 = points.size() - 1; // Check for wrap
    int xend1 = points[endvert1].x;   // Get x & y coordinates
    int yend1 = points[endvert1].y;   // of ending vertices

    // Get ending vertex of edge 2
    int endvert2 = startvert2 + 1;
    if (endvert2 == (points.size()))
        endvert2 = 0;               // Check for wrap
    int xend2 = points[endvert2].x; // Get x & y coordinates
    int yend2 = points[endvert2].y; // of ending vertices

    // Draw the polygon:
    // Continue drawing until all edges drawn
    while (edgecount > 0)
    {
        // Initialize error terms for edges 1 & 2
        errorterm1 = 0;
        errorterm2 = 0;

        // Get absolute value of x & y lengths of edges
        if ((ydiff1 = yend1 - ystart1) < 0)
            ydiff1 = -ydiff1;
        if ((ydiff2 = yend2 - ystart2) < 0)
            ydiff2 = -ydiff2;
        // Get value of length & Calculate X increment
        if ((xdiff1 = xend1 - xstart1) < 0)
        {
            xunit1 = -1;
            xdiff1 = -xdiff1;
        }
        else
        {
            xunit1 = 1;
        }
        // Get value of length & Calculate X increment
        if ((xdiff2 = xend2 - xstart2) < 0)
        {
            xunit2 = -1;
            xdiff2 = -xdiff2;
        }
        else
        {
            xunit2 = 1;
        }

        // Choose which of four routines to use:

        // If X length of edge 1 is greater than y length
        if (xdiff1 > ydiff1)
        {
            // If X length of edge 2 is greater than y length
            if (xdiff2 > ydiff2)
            {
                // Increment edge 1 on X and edge 2 on X:
                count1 = xdiff1; // Count for x increment on edge 1
                count2 = xdiff2; // Count for x increment on edge 2

                // Continue drawing until one edge is done
                while (count1 && count2)
                {
                    // Calculate edge 1:
                    while ((errorterm1 < xdiff1) && (count1 > 0))
                    {
                        // Finished w/edge 1?
                        if (count1--)
                        { // Count down on edge 1
                            // Increment pixel offset
                            xstart1 += xunit1;
                        }
                        // Increment error term
                        errorterm1 += ydiff1;
                        if (errorterm1 < xdiff1)
                        { // If not more than XDIFF
                            SDL_RenderDrawPoint(renderer, xstart1, ystart1);
                        }
                    }
                    errorterm1 -= xdiff1; // If time to increment X, restore error term

                    // Calculate edge 2:
                    while ((errorterm2 < xdiff2) && (count2 > 0))
                    { // Finished w/edge 2?
                        if (count2--)
                        { // Count down on edge 2
                            // start2.x += xunit2; // Increment pixel offset
                            xstart2 += xunit2;
                        }
                        errorterm2 += ydiff2; // Increment error term
                        if (errorterm2 < xdiff2)
                        { // If not more than XDIFF
                          // screen_buffer[offset2] = polygon.color; // ...plot a pixel
                            SDL_RenderDrawPoint(renderer, xstart2, ystart2);
                        }
                    }
                    errorterm2 -= xdiff2; // If time to increment X, restore error term

                    // Draw line from edge 1 to edge 2:
                    // length = offset2 - offset1; // Determine length of horizontal line
                    length = xstart2 - xstart1; // Determine length of horizontal line
                    if (length < 0)
                    {                     // If negative...
                        length = -length; // Make it positive
                        start = xstart2;  // And set START to edge 2
                    }
                    else
                        start = xstart1; // Else set START to edge 1
                    // Draw a line From edge to edge
                    for (int i = start; i < start + length + 1; i++)
                        SDL_RenderDrawPoint(renderer, i, ystart1);
                    // Advance edge 1 offset to next line
                    ystart1++;
                    ystart2++;
                }
            }
            else
            {

                // Increment edge 1 on X and edge 2 on Y:
                count1 = xdiff1; // Count for X increment on edge 1
                count2 = ydiff2; // Count for Y increment on edge 2
                while (count1 && count2)
                { // Continue drawing until one edge is done

                    // Calculate edge 1:
                    while ((errorterm1 < xdiff1) && (count1 > 0))
                    { // Finished w/edge 1?
                        if (count1--)
                        { // Count down on edge 1
                            // start1.x += xunit1; // Increment pixel offset
                            xstart1 += xunit1;
                        }
                        errorterm1 += ydiff1; // Increment error term
                        if (errorterm1 < xdiff1)
                        { // If not more than XDIFF
                            // screen_buffer[offset1] = polygon.color; // ...plot a pixel
                            SDL_RenderDrawPoint(renderer, xstart1, ystart1);
                        }
                    }
                    errorterm1 -= xdiff1; // If time to increment X, restore error term

                    // Calculate edge 2:
                    errorterm2 += xdiff2; // Increment error term
                    if (errorterm2 >= ydiff2)
                    {                         // If time to increment Y...
                        errorterm2 -= ydiff2; // ...restore error term
                        // start2.x += xunit2;   // ...and advance offset to next pixel
                        xstart2 += xunit2;
                    }
                    --count2;

                    // Draw line from edge 1 to edge 2:
                    length = xstart2 - xstart1; // Determine length of horizontal line
                    if (length < 0)
                    {                     // If negative...
                        length = -length; // ...make it positive
                        start = xstart2;  // And set START to edge 2
                    }
                    else
                        start = xstart1;                             // Else set START to edge 1
                    for (int i = start; i < start + length + 1; i++) // From edge to edge
                        // screen_buffer[i] = polygon.color;            // ...draw the linee
                        SDL_RenderDrawPoint(renderer, i, ystart1);
                    // Advance edge 1 offset to next line
                    ystart1++;
                    ystart2++;
                }
            }
        }
        else
        {
            if (xdiff2 > ydiff2)
            {

                // Increment edge 1 on Y and edge 2 on X:
                count1 = ydiff1; // Count for Y increment on edge 1
                count2 = xdiff2; // Count for X increment on edge 2
                while (count1 && count2)
                { // Continue drawing until one edge is done

                    // Calculate edge 1:
                    errorterm1 += xdiff1; // Increment error term
                    if (errorterm1 >= ydiff1)
                    {                         // If time to increment Y...
                        errorterm1 -= ydiff1; // ...restore error term
                        // start1.x += xunit1;   // ...and advance offset to next pixel
                        xstart1 += xunit1;
                    }
                    --count1;

                    // Calculate edge 2:
                    while ((errorterm2 < xdiff2) && (count2 > 0))
                    { // Finished w/edge 1?
                        if (count2--)
                        { // Count down on edge 2
                            // start2.x += xunit2; // Increment pixel offset
                            xstart2 += xunit2;
                        }
                        errorterm2 += ydiff2; // Increment error term
                        if (errorterm2 < xdiff2)
                        { // If not more than XDIFF
                            // screen_buffer[offset2] = polygon.color; // ...plot a pixel
                            SDL_RenderDrawPoint(renderer, xstart2, ystart2);
                        }
                    }
                    errorterm2 -= xdiff2; // If time to increment X, restore error term

                    // Draw line from edge 1 to edge 2:
                    length = xstart2 - xstart1; // Determine length of horizontal line
                    if (length < 0)
                    {                     // If negative...
                        length = -length; // ...make it positive
                        start = xstart2;  // And set START to edge 2
                    }
                    else
                        start = xstart1;                             // Else set START to edge 1
                    for (int i = start; i < start + length + 1; i++) // From edge to edge...
                        // screen_buffer[i] = polygon.color;            // ...draw the line
                        SDL_RenderDrawPoint(renderer, i, ystart1);
                    // Advance edge 1 offset to next line
                    ystart1++;
                    ystart2++;
                }
            }
            else
            {

                // Increment edge 1 on Y and edge 2 on Y:
                count1 = ydiff1; // Count for Y increment on edge 1
                count2 = ydiff2; // Count for Y increment on edge 2
                while (count1 && count2)
                { // Continue drawing until one edge is done

                    // Calculate edge 1:
                    errorterm1 += xdiff1; // Increment error term
                    if (errorterm1 >= ydiff1)
                    {                         // If time to increment Y
                        errorterm1 -= ydiff1; // ...restore error term
                        // start1.x += xunit1;   // ...and advance offset to next pixel
                        xstart1 += xunit1;
                    }
                    --count1;

                    // Calculate edge 2:
                    errorterm2 += xdiff2; // Increment error term
                    if (errorterm2 >= ydiff2)
                    {                         // If time to increment Y
                        errorterm2 -= ydiff2; // ...restore error term
                        // start2.x += xunit2;   // ...and advance offset to next pixel
                        xstart2 += xunit2;
                    }
                    --count2;

                    // Draw line from edge 1 to edge 2:
                    length = xstart2 - xstart1; // Determine length of horizontal line
                    if (length < 0)
                    {                     // If negative...
                        length = -length; // ...make it positive
                        start = xstart2;  // And set START to edge 2
                    }
                    else
                        start = xstart1;                             // Else set START to edge 1
                    for (int i = start; i < start + length + 1; i++) // From edge to edge
                        // screen_buffer[i] = polygon.color;            // ...draw the linee
                        SDL_RenderDrawPoint(renderer, i, ystart1);
                    // Advance edge 1 offset to next line
                    ystart1++;
                    ystart2++;
                }
            }
        }

        // Another edge (at least) is complete. Start next edge, if any.
        if (!count1)
        {                          // If edge 1 is complete...
            --edgecount;           // Decrement the edge count
            startvert1 = endvert1; // Make ending vertex into start vertex
            --endvert1;            // And get new ending vertex
            if (endvert1 < 0)
                endvert1 = points.size() - 1; // Check for wrap
            xend1 = points[endvert1].x;       // Get x & y of new end vertex
            yend1 = points[endvert1].y;
        }
        if (!count2)
        {                          // If edge 2 is complete...
            --edgecount;           // Decrement the edge count
            startvert2 = endvert2; // Make ending vertex into start vertex
            endvert2++;            // And get new ending vertex
            if (endvert2 == (points.size()))
                endvert2 = 0;           // Check for wrap
            xend2 = points[endvert2].x; // Get x & y of new end vertex
            yend2 = points[endvert2].y;
        }
    }
}

void Draw::TriangleFilled(SDL_Renderer *renderer, std::vector<Point2d> points)
{
    std::vector<Point2d> edges;
    GenerateScanlinesForEdge(points[0], points[1], &edges);
    GenerateScanlinesForEdge(points[1], points[2], &edges);
    GenerateScanlinesForEdge(points[2], points[0], &edges);

    //  Sort scanlines by y
    std::sort(edges.begin(), edges.end(),
              [](const Point2d &lhs, const Point2d &rhs)
              {
                  return lhs.y < rhs.y;
              });
    // std::cout << "===================" << std::endl;
    //     for (Point2d point : edges)
    //     {
    //         std::cout << point.y << "/" << point.x << std::endl;
    //     }
    // for (int n = 0; n < edges.size(); n += 2)
    //{
    //     std::cout << edges[n].y << "/" << edges[n].x << " - " << edges[n + 1].y << "/" << edges[n + 1].x << std::endl;
    // }

    //  Print scanlines verifying run from left to right
    for (int n = 0; n < edges.size() - 1; n += 2)
    {
        int xl = edges[n].x;
        int xr = edges[n + 1].x;

        if (xl > xr)
        {
            xl = edges[n + 1].x;
            xr = edges[n].x;
        }

        SDL_RenderDrawLine(renderer, xl, edges[n].y, xr, edges[n].y);
    }
}

void Draw::GenerateScanlinesForEdge(Point2d p1, Point2d p2, std::vector<Point2d> *edges)
{
    //  Check if it is a flat edge and skip it
    if (p1.y == p2.y)
    {
        return;
    }

    int y1 = p1.y;
    int y2 = p2.y;
    int x1 = p1.x;
    int x2 = p2.x;

    if (p1.y > p2.y)
    {
        y1 = p2.y;
        y2 = p1.y;
        x1 = p2.x;
        x2 = p1.x;
    }
    int deltax = x2 - x1;
    int deltay = y2 - y1;

    float step = (float)deltax / (float)deltay;
    int t = 0;
    while (t < deltay)
    {
        int xt = x1 + round(step * (float)t);
        edges->push_back(Point2d(xt, y1 + t));
        t++;
    }
}
