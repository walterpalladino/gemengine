
#include "math/Plane.h"

Plane::Plane()
{
	normal = Vector3d(0.0f, 0.0f, 0.0f);
	intercept = 0.0f;
}

Plane::Plane(Vector3d pNormal, float pIntercept)
{
	normal = pNormal;
	intercept = pIntercept;
}

Plane::Plane(const Plane &rhs)
{
	normal = rhs.normal;
	intercept = rhs.intercept;
}

void Plane::Set(Vector3d pNormal, float pIntercept)
{
	normal = pNormal;
	intercept = pIntercept;
}

void Plane::SetFromPoints(const Vector3d &p0, const Vector3d &p1, const Vector3d &p2)
{
	normal = (p1 - p0).Cross(p2 - p0);
	normal.Normalize();
	CalculateIntercept(p0);
}

void Plane::Normalize()
{
	float normalLength = normal.GetLength();
	normal /= normalLength;
	intercept /= normalLength;
}

// find point of intersection of 3 Planes
bool Plane::Intersect3(const Plane &p2, const Plane &p3, Vector3d &result)
{
	float denominator = normal.Dot((p2.normal).Cross(p3.normal));
	// scalar triple product of normals
	if (denominator == 0.0f) // if zero
		return false;		 // no intersection

	Vector3d temp1, temp2, temp3;

	temp1 = (p2.normal.Cross(p3.normal)) * intercept;
	temp2 = (p3.normal.Cross(normal)) * p2.intercept;
	temp3 = (normal.Cross(p2.normal)) * p3.intercept;

	result = (temp1 + temp2 + temp3) / (-denominator);

	return true;
}

float Plane::GetDistance(const Vector3d &point) const
{
	return point.x * normal.x + point.y * normal.y + point.z * normal.z + intercept;
}

int Plane::ClassifyPoint(const Vector3d &point) const
{
	float plane_distance;

	//	plane_distance = point.x*normal.x + point.y*normal.y + point.z*normal.z + intercept ;
	plane_distance = point.Dot(normal) + intercept;

	if (plane_distance > EPSILON) //==0.0f is too exact, give a bit of room
		return POINT_IN_FRONT_OF_PLANE;

	if (plane_distance < -EPSILON)
		return POINT_BEHIND_PLANE;

	return POINT_ON_PLANE; // otherwise
}

int Plane::ClassifyPoint(const float *point) const
{
	float plane_distance = point[0] * normal.x + point[1] * normal.y + point[2] * normal.z + intercept;

	if (plane_distance > EPSILON) //==0.0f is too exact, give a bit of room
		return POINT_IN_FRONT_OF_PLANE;

	if (plane_distance < -EPSILON)
		return POINT_BEHIND_PLANE;

	return POINT_ON_PLANE; // otherwise
}

Plane Plane::lerp(const Plane &p2, float factor)
{
	Plane result;

	result.normal = normal * (1.0f - factor) + p2.normal * factor;
	result.normal.Normalize();

	result.intercept = intercept * (1.0f - factor) + p2.intercept * factor;

	return result;
}

bool Plane::operator==(const Plane &rhs) const
{
	if (normal == rhs.normal && intercept == rhs.intercept)
		return true;
	else
		return false;
}

bool Plane::IntersectRay(const Vector3d &rayOrigin, const Vector3d &rayDestination, Vector3d &interceptionPoint) const
{
	Vector3d rayDirection;
	double t;
	double numer;
	double denom;

	rayDirection = rayDestination - rayOrigin;
	rayDirection.Normalize();

	denom = normal.Dot(rayDirection);
	if (denom == 0)
		return false;

	numer = -(normal.Dot(rayOrigin) + intercept);

	t = (numer / denom);

	interceptionPoint = rayOrigin + rayDirection * (t);

	return true;
}

bool Plane::IntersectRayDistance(const Vector3d &rayOrigin, const Vector3d &rayDirection, float &pDistance) const
{
	double t;
	double numer;
	double denom;

	denom = normal.Dot(rayDirection);
	if (denom == 0)
		return false;

	numer = -(normal.Dot(rayOrigin) + intercept);

	t = (numer / denom);

	pDistance = (float)t;

	return true;
}

bool Plane::IntersectRayDistance(const Ray3d &pRay, float &pDistance) const
{
	double t;
	double numer;
	double denom;

	denom = normal.Dot(pRay.direction);
	if (denom == 0)
		return false;

	numer = -(normal.Dot(pRay.origin) + intercept);

	t = (numer / denom);

	pDistance = (float)t;

	return true;
}

bool Plane::IntersectSegment(const Vector3d &rayOrigin, const Vector3d &rayDestination, Vector3d &interceptionPoint) const
{
	Vector3d rayDirection;
	double t;
	double numer;
	double denom;
	double rayLength;

	rayDirection = rayDestination - rayOrigin;
	rayLength = rayDirection.GetLength();
	rayDirection.Normalize();

	denom = normal.Dot(rayDirection);
	if (denom == 0)
		return false;

	numer = -(normal.Dot(rayOrigin) + intercept);

	t = (numer / denom);

	if (t > rayLength)
		return false;
	interceptionPoint = rayOrigin + rayDirection * (t);

	return true;
}
