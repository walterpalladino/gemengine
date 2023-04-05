
#pragma once

#include "math/Vector3d.h"

class Ray3d
{
public:
	Vector3d origin;
	Vector3d direction;

public:
	Ray3d(void);
	Ray3d(Vector3d pOrigin, Vector3d pDirection);
};
