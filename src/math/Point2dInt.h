
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
};
