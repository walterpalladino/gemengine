
#include "math/Ray3d.h"

Ray3d::Ray3d(void)
{
	origin.Set(0.0, 0.0, 0.0);
	direction.Set(0.0, 1.0, 0.0);
}

Ray3d::Ray3d(Vector3d pOrigin, Vector3d pDirection)
{
	origin = pOrigin;
	direction = pDirection;
	direction.Normalize();
}
