#pragma once

#include "math/Vector3d.h"

#define CW_PLANE_BACKSIDE 0x000001
#define CW_PLANE_FRONT 0x000010
#define CW_ON_PLANE 0x000100

class Plane3d
{
public:
	Vector3d origin;
	Vector3d normal;
	float intercept;

public:
	Plane3d(void);

	bool Set(const Vector3d pP0, const Vector3d pP1, const Vector3d pP2);

	double IntersectRay(Vector3d rOrigin, Vector3d rVector);
	long ClassifyPoint(Vector3d pPoint);

	double GetDistance(Vector3d pPoint);
};
