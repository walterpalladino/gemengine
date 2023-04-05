
#pragma once

#include "math/Vector3d.h"
#include "math/Ray3d.h"

#ifndef EPSILON
#define EPSILON 0.01f
#endif

// constants for ClassifyPoint()
const int POINT_ON_PLANE = 0;
const int POINT_IN_FRONT_OF_PLANE = 1;
const int POINT_BEHIND_PLANE = 2;

class Plane
{
public:
	Plane();
	Plane(Vector3d pNormal, float pIntercept);
	Plane(const Plane &rhs);

	~Plane() {}

	void Set(Vector3d pNormal, float pIntercept);

	void SetNormal(const Vector3d &rhs) { normal = rhs; }
	void SetIntercept(float pIntercept) { intercept = pIntercept; }
	void SetFromPoints(const Vector3d &p0, const Vector3d &p1, const Vector3d &p2);

	void CalculateIntercept(const Vector3d &pointOnPlane) { intercept = -normal.Dot(pointOnPlane); }

	void Normalize(void);

	Vector3d GetNormal() { return normal; }
	float GetIntercept() { return intercept; }

	// find point of intersection of 3 Planes
	bool Intersect3(const Plane &p2, const Plane &p3, Vector3d &result);

	//	Vector3d	IntersectRay(const Vector3d & rayOrig, const Vector3d & rayDest ) const ;
	bool IntersectRayDistance(const Vector3d &rayOrigin, const Vector3d &rayDirection, float &pDistance) const;
	bool IntersectRayDistance(const Ray3d &pRay, float &pDistance) const;
	bool IntersectRay(const Vector3d &rayOrigin, const Vector3d &rayDestination, Vector3d &interceptionPoint) const;
	bool IntersectSegment(const Vector3d &rayOrigin, const Vector3d &rayDestination, Vector3d &interceptionPoint) const;

	float GetDistance(const Vector3d &point) const;

	int ClassifyPoint(const Vector3d &point) const;
	int ClassifyPoint(const float *point) const;

	Plane lerp(const Plane &p2, float factor);

	// operators
	bool operator==(const Plane &rhs) const;
	bool operator!=(const Plane &rhs) const
	{
		return !((*this) == rhs);
	}

	// unary operators
	Plane operator-(void) const
	{
		return Plane(-normal, -intercept);
	}

	Plane operator+(void) const
	{
		return (*this);
	}

	// member variables
	Vector3d normal; // X.N+intercept=0
	float intercept;
};
