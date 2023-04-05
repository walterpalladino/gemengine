#pragma once

#include "math/Vector3d.h"
#include "math/Plane.h"
#include "math/Matrix4x4.h"

bool IntersectPlaneRay(const Plane plane, const Vector3d &rayOrig, const Vector3d &rayDest, Vector3d vResult);

bool RayTrianleIntersection(Vector3d *ray, Vector3d *triangle, Vector3d *point);

/*
class Ray3d
{
public:

	// ray origin
	float	x ;
	float	y ;
	float	z ;
	// ray direction
	float	i ;
	float	j ;
	float	k ;

	// inverse ray direction
	float	ii ;
	float	ij ;
	float	ik ;

	// ray slopes
	float	s_yx ;
	float	s_xy ;
	float	s_zy ;
	float	s_yz ;
	float	s_xz ;
	float	s_zx ;

	// precomputation
	float	c_xy ;
	float	c_yx ;
	float	c_zy ;
	float	c_yz ;
	float	c_xz ;
	float	c_zx ;

	void Make( Vector3d orig, Vector3d dest ) ;

} ;
*/

bool RayTriangleIntersect(Vector3d ray_origin,
						  Vector3d ray_direction,
						  Vector3d vert0,
						  Vector3d vert1,
						  Vector3d vert2,
						  Vector3d *intercept);

// bool RaySphereIntersect ( Vector3d rayOrigin, Vector3d rV, Vector3d sO, double sphereRadius, double & time ) ;
bool RaySphereIntersect(const Vector3d &rayOrigin, const Vector3d &rayDestination, const Vector3d sphereCentre, float sphereRadius, float *t);

#define PLANE_BACKSIDE 0x000001
#define PLANE_FRONT 0x000010
#define ON_PLANE 0x000100

double intersectRayPlane(Vector3d rOrigin, Vector3d rVector, Vector3d pOrigin, Vector3d pNormal);
double intersectRaySphere(Vector3d rO, Vector3d rV, Vector3d sO, double sR);
bool CheckPointInTriangle(Vector3d point, Vector3d a, Vector3d b, Vector3d c);
Vector3d closestPointOnLine(Vector3d &a, Vector3d &b, Vector3d &p);
Vector3d closestPointOnTriangle(Vector3d a, Vector3d b, Vector3d c, Vector3d p);
bool CheckPointInSphere(Vector3d point, Vector3d sO, double sR);
Vector3d tangentPlaneNormalOfEllipsoid(Vector3d point, Vector3d eO, Vector3d eR);
long classifyPoint(Vector3d point, Vector3d pO, Vector3d pN);
