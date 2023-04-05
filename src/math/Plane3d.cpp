
#include "math/Plane3d.h"

Plane3d::Plane3d(void)
{
}

bool Plane3d::Set(const Vector3d pP0, const Vector3d pP1, const Vector3d pP2)
{
	Vector3d v1, v2;

	origin = pP0;
	v1 = pP1 - pP0;
	v2 = pP2 - pP0;

	// You might not need this if you KNOW all your triangles are valid
	if ((v1.IsZero() || v2.IsZero()))
		return true;

	// if a valid plane
	// determine normal to plane containing polygon
	normal = v1.Cross(v2);
	normal.Normalize();

	intercept = -normal.Dot(pP0);
	intercept = -normal.Dot(pP1);
	intercept = -normal.Dot(pP2);

	return false;
}

double Plane3d::IntersectRay(Vector3d rOrigin, Vector3d rVector)
{
	double d;
	double numer;
	double denom;

	d = -(normal.Dot(origin));
	numer = normal.Dot(rOrigin) + d;
	denom = normal.Dot(rVector);

	if (denom == 0) // normal is orthogonal to vector, cant intersect
		return (-1.0f);

	return -(numer / denom);
}

long Plane3d::ClassifyPoint(Vector3d pPoint)
{
	Vector3d dir;
	double d;

	dir = origin - pPoint;
	d = dir.Dot(normal);

	if (d < -0.001f)
		return CW_PLANE_FRONT;
	else if (d > 0.001f)
		return CW_PLANE_BACKSIDE;

	return CW_ON_PLANE;
}

double Plane3d::GetDistance(Vector3d pPoint)
{
	//	return point.x*normal.x + point.y*normal.y + point.z*normal.z + intercept;
	return normal.Dot(pPoint) + intercept;
}
