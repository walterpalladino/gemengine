

#include "math/Math3d.h"
#include "math/MathCommons.h"

/*
// Copyright 2001, softSurfer (www.softsurfer.com)
// This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from its use.
// Users of this code must verify correctness for their application.


// Assume that classes are already given for the objects:
//    Point and Vector with
//        coordinates {float x, y, z;}
//        operators for:
//            == to test equality
//            != to test inequality
//            (Vector)0 = (0,0,0)         (null vector)
//            Point  = Point � Vector
//            Vector = Point - Point
//            Vector = Scalar * Vector    (scalar product)
//            Vector = Vector * Vector    (cross product)
//    Line and Ray and Segment with defining points {Point P0, P1;}
//        (a Line is infinite, Rays and Segments start at P0)
//        (a Ray extends beyond P1, but a Segment ends at P1)
//    Plane with a point and a normal {Point V0; Vector n;}
//    Triangle with defining vertices {Point V0, V1, V2;}
//    Polyline and Polygon with n vertices {int n; Point *V;}
//        (a Polygon has V[n]=V[0])
//===================================================================


#define SMALL_NUM  0.00000001 // anything that avoids division overflow
// dot product (3D) which allows vector operations in arguments
#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z)


// intersect_RayTriangle(): intersect a ray with a 3D triangle
//    Input:  a ray R, and a triangle T
//    Output: *I = intersection point (when it exists)
//    Return: -1 = triangle is degenerate (a segment or point)
//             0 = disjoint (no intersect)
//             1 = intersect in unique point I1
//             2 = are in the same plane
int Vector3d::IntersectRayTriangle( Ray R, Triangle T, Point* I )
{
Vector3d	u, v, n;             // triangle vectors
Vector3d	dir, w0, w;          // ray vectors
float		r, a, b;             // params to calc ray-plane intersect

	// get triangle edge vectors and plane normal
	u = T.V1 - T.V0;
	v = T.V2 - T.V0;
	n = u * v;             // cross product
	if (n == (Vector)0)            // triangle is degenerate
	return -1;                 // do not deal with this case

	dir = R.P1 - R.P0;             // ray direction vector
	w0 = R.P0 - T.V0;
	a = -dot(n,w0);
	b = dot(n,dir);
	if (fabs(b) < SMALL_NUM) {     // ray is parallel to triangle plane
	if (a == 0)                // ray lies in triangle plane
	return 2;
	else return 0;             // ray disjoint from plane
	}

	// get intersect point of ray with triangle plane
	r = a / b;
	if (r < 0.0)                   // ray goes away from triangle
	return 0;                  // => no intersect
	// for a segment, also test if (r > 1.0) => no intersect

	*I = R.P0 + r * dir;           // intersect point of ray and plane

	// is I inside T?
	float    uu, uv, vv, wu, wv, D;
	uu = dot(u,u);
	uv = dot(u,v);
	vv = dot(v,v);
	w = *I - T.V0;
	wu = dot(w,u);
	wv = dot(w,v);
	D = uv * uv - uu * vv;

	// get and test parametric coords
	float s, t;
	s = (uv * wv - vv * wu) / D;
	if (s < 0.0 || s > 1.0)        // I is outside T
	return 0;
	t = (uv * wu - uu * wv) / D;
	if (t < 0.0 || (s + t) > 1.0)  // I is outside T
	return 0;

	return 1;                      // I is in T
}
*/

bool RayTrianleIntersection(Vector3d *ray, Vector3d *triangle, Vector3d *point)
{
	return false;
}

/*
 // What the code do ?
 //
 // This code calculate this formula :
 //   deplacement = [R]deplacement'
 //
 // deplacement : deplacement in the fixed coordinate system
 // deplacement' : deplacement in the camera coordinate system
 // [R] = [Ry][Rx]
 // [Ry] : y rotation matrix (rotate y first)
 // [Rx] : x rotation matrix
 //
 // This kind of deplacement is generally used for free deplacement (ie move everywhere).
 // Take an example, if you're looking at the sky and you want to move forward.
 // The forward deplacement is in direction to the up, so you will fly !

public Vector3f toVectorInFixedSystem1(float dx, float dy, float dz)
{
	//Don't calculate for nothing ...
	if(dx == 0.0f & dy == 0.0f && dz == 0.0f)
		 return new Vector3f();

	//Convert to Radian : 360� = 2PI
	double xRot = toRadians(orientation.getX());    //Math.toRadians is toRadians in Java 1.5 (static import)
	double yRot = toRadians(orientation.getY());

	//Calculate the formula
	float x = (float)( dx*cos(yRot) + dy*sin(xRot)*sin(yRot) - dz*cos(xRot)*sin(yRot) );
	float y = (float)(              + dy*cos(xRot)           + dz*sin(xRot)           );
	float z = (float)( dx*sin(yRot) - dy*sin(xRot)*cos(yRot) + dz*cos(xRot)*cos(yRot) );

	//Return the vector expressed in the global axis system
	return new Vector3f(x, y, z);
}


 // This kind of deplacement generaly used for player movement (in shooting game ...).
 // The x rotation is 'ignored' for the calculation of the deplacement.
 // This result that if you look upward and you want to move forward,
 // the deplacement is calculated like if your were parallely to the ground.

public Vector3f toVectorInFixedSystem2(float dx, float dy, float dz)
{
	//Don't calculate for nothing ...
	if(dx == 0.0f & dy == 0.0f && dz == 0.0f)
		 return new Vector3f();

	//Convert to Radian : 360� = 2PI
	double yRot = toRadians(orientation.getY());    //Math.toRadians is toRadians in Java 1.5 (static import)

	//Calculate the formula
	float x = (float)( dx*cos(yRot) + 0            - dz*sin(yRot) );
	float y = (float)( 0            + dy*cos(xRot) + 0            );
	float z = (float)( dx*sin(yRot) + 0            + dz*cos(yRot) );

	//Return the vector expressed in the global axis system
	return new Vector3f(x, y, z);
}
*/

bool IntersectPlaneRay(const Plane plane, const Vector3d &rayOrig, const Vector3d &rayDest, Vector3d vResult)
{
	Vector3d vPoint;
	Vector3d vLineDir; // Variables to hold the point and the line's direction

	double Numerator = 0.0,
		   Denominator = 0.0,
		   dist = 0.0;

	// Here comes the confusing part.  We need to find the 3D point that is actually
	// on the plane.  Here are some steps to do that:

	// 1)  First we need to get the vector of our line, Then normalize it so it's a length of 1
	vLineDir = rayDest - rayOrig; // Get the Vector of the line
	vLineDir.Normalize();		  // Normalize the lines vector

	// 2) Use the plane equation (distance = Ax + By + Cz + D) to find the distance from one of our points to the plane.
	//    Here I just chose a arbitrary point as the point to find that distance.  You notice we negate that
	//    distance.  We negate the distance because we want to eventually go BACKWARDS from our point to the plane.
	//    By doing this is will basically bring us back to the plane to find our intersection point.
	Numerator = -(plane.normal.x * rayOrig.x + // Use the plane equation with the normal and the line
				  plane.normal.y * rayOrig.y +
				  plane.normal.z * rayOrig.z + plane.intercept);

	// 3) If we take the dot product between our line vector and the normal of the polygon,
	//    this will give us the cosine of the angle between the 2 (since they are both normalized - length 1).
	//    We will then divide our Numerator by this value to find the offset towards the plane from our arbitrary point.
	Denominator = plane.normal.Dot(vLineDir); // Get the dot product of the line's vector and the normal of the plane

	// Since we are using division, we need to make sure we don't get a divide by zero error
	// If we do get a 0, that means that there are INFINATE points because the the line is
	// on the plane (the normal is perpendicular to the line - (Normal.Vector = 0)).
	// In this case, we should just return any point on the line.

	if (Denominator == 0.0) // Check so we don't divide by zero
		return false;		// Return an arbitrary point on the line

	// We divide the (distance from the point to the plane) by (the dot product)
	// to get the distance (dist) that we need to move from our arbitrary point.  We need
	// to then times this distance (dist) by our line's vector (direction).  When you times
	// a scalar (single number) by a vector you move along that vector.  That is what we are
	// doing.  We are moving from our arbitrary point we chose from the line BACK to the plane
	// along the lines vector.  It seems logical to just get the numerator, which is the distance
	// from the point to the line, and then just move back that much along the line's vector.
	// Well, the distance from the plane means the SHORTEST distance.  What about in the case that
	// the line is almost parallel with the polygon, but doesn't actually intersect it until half
	// way down the line's length.  The distance from the plane is short, but the distance from
	// the actual intersection point is pretty long.  If we divide the distance by the dot product
	// of our line vector and the normal of the plane, we get the correct length.  Cool huh?

	dist = Numerator / Denominator; // Divide to get the multiplying (percentage) factor

	// Now, like we said above, we times the dist by the vector, then add our arbitrary point.
	// This essentially moves the point along the vector to a certain distance.  This now gives
	// us the intersection point.  Yay!
	/*
		vPoint.x = (float)(rayOrig.x + (vLineDir.x * dist));
		vPoint.y = (float)(rayOrig.y + (vLineDir.y * dist));
		vPoint.z = (float)(rayOrig.z + (vLineDir.z * dist));
	*/
	vPoint = rayOrig + (vLineDir * dist);

	vResult = vPoint;

	return true; // Return the intersection point
}

/*
public static bool PlaneIntersectRay(ref Plane p, ref Ray r, out float fDist)
{
	fDist = 0;
	float denom = Vector3.Dot(p.Normal,r.Direction);
	if (denom == 0) return false;
	float numer = p.Normal.Dot(r.Position);
	fDist = -(((numer + p.D)) / denom);
	return true;
}

*/

/*
void Ray3d::Make( Vector3d orig, Vector3d dest )
{
Vector3d	dir ;

	//	Get the ray direction
	dir	= (dest - orig) ;
	dir.Normalize() ;

	x	= orig.x ;
	y	= orig.y ;
	z	= orig.z ;

	if (dir.x==0.0f)
		i	= 0.000001 ;
	else
		i	= dir.x ;
	if (dir.y==0.0f)
		j	= 0.000001 ;
	else
		j	= dir.y ;
	if (dir.z==0.0f)
		k	= 0.000001 ;
	else
		k	= dir.z ;

	ii = 1.0f/i; // inverse ray direction
	ij = 1.0f/j;
	ik = 1.0f/k;

	s_yx = i * ij; // ray slopes
	s_xy = j * ii;
	s_zy = j * ik;
	s_yz = k * ij;
	s_xz = i * ik;
	s_zx = k * ii;

	c_xy = y - s_xy * x; // precomputation
	c_yx = x - s_yx * y;
	c_zy = y - s_zy * z;
	c_yz = z - s_yz * y;
	c_xz = z - s_xz * x;
	c_zx = x - s_zx * z;

}
*/

bool RayTriangleIntersect(Vector3d ray_origin,
						  Vector3d ray_direction,
						  Vector3d vert0,
						  Vector3d vert1,
						  Vector3d vert2,
						  Vector3d *intercept)
{
	Vector3d edge1;
	Vector3d edge2;

	Vector3d tvec, pvec, qvec;
	float det, inv_det;

	float t, u, v;

	t = 0;
	u = 0;
	v = 0;

	edge1 = vert1 - vert0;
	edge2 = vert2 - vert0;

	pvec = ray_direction.Cross(edge2);

	det = edge1.Dot(pvec);

	if (det > -0.00001f)
		return false;

	inv_det = 1.0f / det;

	tvec = ray_origin - vert0;

	u = tvec.Dot(pvec) * inv_det;
	if (u < -0.001f || u > 1.001f)
		return false;

	qvec = tvec.Cross(edge1);

	v = ray_direction.Dot(qvec) * inv_det;
	if (v < -0.001f || u + v > 1.001f)
		return false;

	t = edge2.Dot(qvec) * inv_det;

	if (t <= 0)
		return false;

	intercept->x = t;
	intercept->y = u;
	intercept->z = v;

	return true;
}

/*
bool RaySphereIntersect ( Vector3d rayOrigin, Vector3d rV, Vector3d sO, double sphereRadius, double & time )
{
Vector3d	rayDirection ;
double		rayMagnitud ;
double		v ;
double		d ;

	rayDirection	= rayDestination - rayOrigin;
	rayMagnitud		= rayDirection.Magnitude() ;
	v	= rayDirection.Dot ( rV ) ;
	d	= (sphereRadius*sphereRadius) - (c*c - v*v) ;

	// If there was no intersection, return -1
	if (d < 0.0)
	{
		time	= 0 ;
		return false ;
	}

	// Return the distance to the [first] intersecting point
	time	= v - sqrt(d);
	return true ;
}
*/
/*
void collisionDetection(Vector3d sourcePoint, Vector3d velocityVector, Vector3d gravityVector) ;
void collideWithWorld( Vector3d sourcePoint, Vector3d velocityVector) ;
Vector3d	radiusVector ;

// The collision detection entry point
void collisionDetection(Vector3d sourcePoint, Vector3d velocityVector, Vector3d gravityVector)
{
	// We need to do any pre-collision detection work here. Such as adding
	// gravity to our velocity vector. We want to do it in this
	// separate routine because the following routine is recursive, and we
	// don't want to recursively add gravity.
	// Add gravity
	velocityVector += gravityVector;
	// At this point, we�ll scale our inputs to the collision routine
	sourcePoint /= radiusVector;
	velocityVector /= radiusVector;
	// Okay! Time to do some collisions
	collideWithWorld(sourcePoint, velocityVector);
	// Our collisions are complete, un-scale the output
	sourcePoint *= radiusVector;
}

// The collision detection�s recursive routine
void collideWithWorld( Vector3d sourcePoint, Vector3d velocityVector)
{
	// How far do we need to go?
	double distanceToTravel = velocityVector.Magnitude();
	// Do we need to bother?
	if (distanceToTravel < EPSILON) return;
	// Whom might we collide with?
	List potentialColliders = determine list of potential colliders;
	// If there are none, we can safely move to the destination and bail
	if (potentialColliders is empty)
	{
		sourcePoint += velocityVector;
		return;
	}
	// You�ll need to write this routine to deal with your specific data
	scale_potential_colliders_to_ellipsoid_space(radiusVector);
	// Determine the nearest collider from the list potentialColliders
	bool collisionFound = false;
	double nearestDistance = -1.0;
	Vector3d nearestIntersectionPoint = NULL;
	Vector3d nearestPolygonIntersectionPoint = NULL;

	for (each polygon in potentialColliders)
	{
		// Plane origin/normal
		Vector3d pOrigin = any vertex from current poly;
		Vector pNormal = surface normal (unit vector) from current poly;
		// Determine the distance from the plane to the source
		Double pDist = intersect(pOrigin, pNormal, source, -pNormal);
		Vector3d sphereIntersectionPoint;
		Vector3d planeIntersectionPoint;
		// Is the source point behind the plane?
		//
		// [note that you can remove this condition if your visuals are not
		// using backface culling]
		if (pDist < 0.0)
		{
			continue;
		}
		// Is the plane embedded (i.e. within the distance of 1.0 for our
		// unit sphere)?
		else if (pDist <= 1.0)
		{
			// Calculate the plane intersection point
			Vector temp = -pNormal with length set to pDist;
			planeIntersectionPoint = source + temp;
		}
		else
		{
			// Calculate the sphere intersection point
			sphereIntersectionPoint = source - pNormal;
			// Calculate the plane intersection point
			Double t = intersect(pOrigin, pNormal,
			sphereIntersectionPoint, Velocity with
			normalized length);
			// Are we traveling away from this polygon?
			if (t < 0.0) continue;
			// Calculate the plane intersection point
			Vector V = velocityVector with length set to t;
			planeIntersectionPoint = sphereIntersectionPoint + V;
		}
		// Unless otherwise noted, our polygonIntersectionPoint is the
		// same point as planeIntersectionPoint
		Vector3d polygonIntersectionPoint = planeIntersectionPoint;
		// So� are they the same?
		if (planeIntersectionPoint is not within the current polygon)
		{
			polygonIntersectionPoint = nearest point on polygon's
			perimeter to planeIntersectionPoint;
		}
		// Invert the velocity vector
		Vector negativeVelocityVector = -velocityVector;
		// Using the polygonIntersectionPoint, we need to reverse-intersect
		// with the sphere (note: the 1.0 below is the unit-sphere�s
		// radius)
		Double t = intersectSphere(sourcePoint, 1.0,
		polygonIntersectionPoint, negativeVelocityVector);
		// Was there an intersection with the sphere?
		if (t >= 0.0 && t <= distanceToTravel)
		{
			// Where did we intersect the sphere?
			Vector V = negativeVelocityVector with length set to t;
			Vector intersectionPoint = polygonIntersectionPoint + V;
			// Closest intersection thus far?
			if (!collisionFound || t < nearestDistance)
			{
				nearestDistance = t;
				nearestIntersectionPoint = intersectionPoint;
				nearestPolygonIntersectionPoint =
				polygonIntersectionPoint;
				collisionFound = true;
			}
		}
	}
	// If we never found a collision, we can safely move to the destination
	// and bail
	if (!collisionFound)
	{
		sourcePoint += velocityVector;
		return;
	}
	// Move to the nearest collision
	Vector V = velocityVector with length set to (nearestDistance - EPSILON);
	sourcePoint += V;
	// What's our destination (relative to the point of contact)?
	Set length of V to (distanceToTravel � nearestDistance);
	Vector3d destinationPoint = nearestPolygonIntersectionPoint + V;
	// Determine the sliding plane
	Vector3d slidePlaneOrigin = nearestPolygonIntersectionPoint;
	Vector slidePlaneNormal = nearestPolygonIntersectionPoint - sourcePoint;
	// We now project the destination point onto the sliding plane
	Double time = intersect(slidePlaneOrigin, slidePlaneNormal,
	destinationPoint, slidePlaneNormal);
	Set length of slidePlaneNormal to time;
	Vector destinationProjectionNormal = slidePlaneNormal;
	Vector3d newDestinationPoint = destination + destinationProjectionNormal;
	// Generate the slide vector, which will become our new velocity vector
	// for the next iteration
	Vector newVelocityVector = newDestinationPoint �
	nearestPolygonIntersectionPoint;
	// Recursively slide (without adding gravity)
	collideWithWorld(sourcePoint, newVelocityVector);
}

*/

//
// Ray-sphere intersection.
// p=(ray origin position - sphere position),
// d=ray direction,
// r=sphere radius,
// Output:
// i1=first intersection distance,
// i2=second intersection distance
// i1<=i2
// i1>=0
// returns true if intersection found,false otherwise.
//
// bool RaySphereIntersect(const Vec3d &p, const Vec3d &d, double r, double  &i1, double &i2){
bool RaySphereIntersect(const Vector3d &rayOrigin, const Vector3d &rayDestination, const Vector3d sphereCentre, float sphereRadius, float *t)
{
	double det, b;
	Vector3d p;
	Vector3d d;
	double i1, i2;

	p = rayOrigin - sphereCentre;
	d = rayDestination - rayOrigin;

	b = -p.Dot(d);

	det = b * b - p.Dot(p) + sphereRadius * sphereRadius;
	if (det < 0)
	{
		return false;
	}
	det = sqrt(det);
	i1 = b - det;
	i2 = b + det;
	// intersecting with ray?
	if (i2 < 0)
		return false;
	if (i1 < 0)
		i1 = 0;
	*t = i1;
	return true;
}

// ----------------------------------------------------------------------
// Name  : intersectRayPlane()
// Input : rOrigin - origin of ray in world space
//         rVector - vector describing direction of ray in world space
//         pOrigin - Origin of plane
//         pNormal - Normal to plane
// Notes : Normalized directional vectors expected
// Return: distance to plane in world units, -1 if no intersection.
// -----------------------------------------------------------------------
double intersectRayPlane(Vector3d rOrigin, Vector3d rVector, Vector3d pOrigin, Vector3d pNormal)
{
	double d;
	double numer;
	double denom;

	d = -(pNormal.Dot(pOrigin));
	numer = pNormal.Dot(rOrigin) + d;
	denom = pNormal.Dot(rVector);

	if (denom == 0) // normal is orthogonal to vector, cant intersect
		return (-1.0f);

	return -(numer / denom);
}

// ----------------------------------------------------------------------
// Name  : intersectRaySphere()
// Input : rO - origin of ray in world space
//         rV - vector describing direction of ray in world space
//         sO - Origin of sphere
//         sR - radius of sphere
// Notes : Normalized directional vectors expected
// Return: distance to sphere in world units, -1 if no intersection.
// -----------------------------------------------------------------------

double intersectRaySphere(Vector3d rO, Vector3d rV, Vector3d sO, double sR)
{
	Vector3d Q;
	double c;
	double v;
	double d;

	Q = sO - rO;

	c = Q.GetLength();
	v = Q.Dot(rV);
	d = sR * sR - (c * c - v * v);

	// If there was no intersection, return -1
	if (d < 0.0)
		return (-1.0f);

	// Return the distance to the [first] intersecting point
	return (v - sqrt(d));
}

// ----------------------------------------------------------------------
// Name  : CheckPointInTriangle()
// Input : point - point we wish to check for inclusion
//         a - first vertex in triangle
//         b - second vertex in triangle
//         c - third vertex in triangle
// Notes : Triangle should be defined in clockwise order a,b,c
// Return: TRUE if point is in triangle, FALSE if not.
// -----------------------------------------------------------------------

bool CheckPointInTriangle(Vector3d point, Vector3d a, Vector3d b, Vector3d c)
{
	double total_angles;

	// make the 3 vectors
	Vector3d v1;
	Vector3d v2;
	Vector3d v3;

	total_angles = 0.0f;

	// make the 3 vectors
	v1 = point - a;
	v2 = point - b;
	v3 = point - c;

	v1.Normalize();
	v2.Normalize();
	v3.Normalize();

	total_angles += acos(v1.Dot(v2));
	total_angles += acos(v2.Dot(v3));
	total_angles += acos(v3.Dot(v1));

	if (fabs(total_angles - 2 * PI) <= 0.005)
		return (true);

	return (false);
}

// ----------------------------------------------------------------------
// Name  : closestPointOnLine()
// Input : a - first end of line segment
//         b - second end of line segment
//         p - point we wish to find closest point on line from
// Notes : Helper function for closestPointOnTriangle()
// Return: closest point on line segment
// -----------------------------------------------------------------------

Vector3d closestPointOnLine(Vector3d &a, Vector3d &b, Vector3d &p)
{
	Vector3d c;
	Vector3d V;

	double d;
	double t;

	// Determine t (the length of the vector from �a� to �p�)
	c = p - a;
	V = b - a;

	d = V.GetLength();

	V.Normalize();
	t = V.Dot(c);

	// Check to see if �t� is beyond the extents of the line segment
	if (t < 0.0f)
		return (a);
	if (t > d)
		return (b);

	// Return the point between �a� and �b�
	// set length of V to t. V is normalized so this is easy
	V = V * t;

	return (a + V);
}

// ----------------------------------------------------------------------
// Name  : closestPointOnTriangle()
// Input : a - first vertex in triangle
//         b - second vertex in triangle
//         c - third vertex in triangle
//         p - point we wish to find closest point on triangle from
// Notes :
// Return: closest point on line triangle edge
// -----------------------------------------------------------------------

Vector3d closestPointOnTriangle(Vector3d a, Vector3d b, Vector3d c, Vector3d p)
{
	Vector3d Rab, Rbc, Rca;

	double dAB, dBC, dCA;

	double min;
	Vector3d result;

	Rab = closestPointOnLine(a, b, p);
	Rbc = closestPointOnLine(b, c, p);
	Rca = closestPointOnLine(c, a, p);

	dAB = (p - Rab).GetLength();
	dBC = (p - Rbc).GetLength();
	dCA = (p - Rca).GetLength();

	min = dAB;
	result = Rab;

	if (dBC < min)
	{
		min = dBC;
		result = Rbc;
	}

	if (dCA < min)
		result = Rca;

	return (result);
}

// ----------------------------------------------------------------------
// Name  : CheckPointInTriangle()
// Input : point - point we wish to check for inclusion
//         sO - Origin of sphere
//         sR - radius of sphere
// Notes :
// Return: TRUE if point is in sphere, FALSE if not.
// -----------------------------------------------------------------------

bool CheckPointInSphere(Vector3d point, Vector3d sO, double sR)
{
	float d;

	d = (point - sO).GetLength();

	if (d <= sR)
		return true;
	return false;
}

// ----------------------------------------------------------------------
// Name  : tangentPlaneNormalOfEllipsoid()
// Input : point - point we wish to compute normal at
//         eO - Origin of ellipsoid
//         eR - radius vector of ellipsoid
// Notes :
// Return: a unit normal vector to the tangent plane of the ellipsoid in the point.
// -----------------------------------------------------------------------
Vector3d tangentPlaneNormalOfEllipsoid(Vector3d point, Vector3d eO, Vector3d eR)
{
	Vector3d p;
	double a2, b2, c2;
	Vector3d res;

	p = point - eO;

	a2 = eR.x * eR.x;
	b2 = eR.y * eR.y;
	c2 = eR.z * eR.z;

	res.x = p.x / a2;
	res.y = p.y / b2;
	res.z = p.z / c2;

	res.Normalize();
	return (res);
}

// ----------------------------------------------------------------------
// Name  : classifyPoint()
// Input : point - point we wish to classify
//         pO - Origin of plane
//         pN - Normal to plane
// Notes :
// Return: One of 3 classification codes
// -----------------------------------------------------------------------

long classifyPoint(Vector3d point, Vector3d pO, Vector3d pN)
{
	Vector3d dir;
	double d;

	dir = pO - point;
	d = dir.Dot(pN);

	if (d < -0.001f)
		return PLANE_FRONT;
	else if (d > 0.001f)
		return PLANE_BACKSIDE;

	return ON_PLANE;
}

Vector3d CalculatePolygonNormal(Vector3d vert1, Vector3d vert2, Vector3d vert3)
{
	Vector3d vec1, vec2;
	Vector3d normal;

	vec1 = vert2 - vert1;
	vec2 = vert3 - vert1;

	normal = vec1.Cross(vec2);

	normal.Normalize();

	return normal;
}
