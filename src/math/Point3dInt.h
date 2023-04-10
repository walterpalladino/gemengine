
#pragma once

struct Point3dInt
{
public:
	int x,
		y,
		z;

	Point3dInt(){};
	Point3dInt(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};
