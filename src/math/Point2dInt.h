
#pragma once

struct Point2dInt
{
public:
	int x,
		y;

	Point2dInt(){};
	Point2dInt(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	Point2dInt(const Point2dInt &p)
	{
		this->x = p.x;
		this->y = p.y;
	}

	Point2dInt operator-(const Point2dInt &p) const
	{
		Point2dInt diff;

		diff.x = x - p.x;
		diff.y = y - p.y;

		return diff;
	}

	static int Cross(Point2dInt p1, Point2dInt p2, Point2dInt p3)
	{
		//	Get the vectors
		Point2dInt v1 = p2 - p1;
		Point2dInt v2 = p3 - p1;

		// Return cross product
		return (v1.x * v2.y - v1.y * v2.x);
	}
};
