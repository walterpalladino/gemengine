
#include <math.h>
#include <float.h>

#include "math/MathCommons.h"
#include "math/Vector3d.h"
#include "math/Matrix3d.h"

//==============================================================================
// Vec 3D

// ===========================================================================
// Name.......: Vec3D()
// Description:	This function is the constructor for Vec3D
// Parameters.: NIL
// Returns....: NIL
// ===========================================================================
Vector3d::Vector3d()
{
	Unit();
}

Vector3d::Vector3d(const float ptAX, const float ptAY, const float ptAZ)
{
	x = ptAX;
	y = ptAY;
	z = ptAZ;
}
/*
Vector3d::Vector3d( const Vector3d ptA)
{
	x	= ptA.x ;
	y	= ptA.y ;
	z	= ptA.z ;

}
*/

// ===========================================================================
// Name.......: DiffPt()
// Description:	This function Sets the vector equal to the difference of two
//				points.
// Parameters.: ptA				- the first point
//				ptB				- the second point
// Returns....: Vector3d			- the difference
// ===========================================================================
Vector3d Vector3d::DiffPt(Vector3d ptA, Vector3d ptB)
{
	x = ptA.x - ptB.x;
	y = ptA.y - ptB.y;
	z = ptA.z - ptB.z;

	return *this;
}

// ===========================================================================
// Name.......: Magnitude()
// Description:	This function returns the magnitude of the vector.
// Parameters.: NIL
// Returns....: float			- the magnitude
// ===========================================================================
double Vector3d::Magnitude(void) const
{
	double q;

	q = x * x;
	q += y * y;
	q += z * z;

	q = sqrt(q);
	return (q);
}

// ===========================================================================
// Name.......: NormalPt()
// Description:	This function Sets the vector equal to the normal of the given
//				triangle.
// Parameters.: ptA				- the first point
//				ptB				- the second point
//				ptC				- the third point
// Returns....: Vector3d			- the normal vector
// ===========================================================================
Vector3d Vector3d::NormalPt(Vector3d ptA, Vector3d ptB, Vector3d ptC)
{
	Vector3d v1;
	Vector3d v2;

	v1.x = ptA.x - ptB.x;
	v1.y = ptA.y - ptB.y;
	v1.z = ptA.z - ptB.z;

	v2.x = ptC.x - ptB.x;
	v2.y = ptC.y - ptB.y;
	v2.z = ptC.z - ptB.z;

	// dot
	x = v1.y * v2.z - v1.z * v2.y;
	y = v1.z * v2.x - v1.x * v2.z;
	z = v1.x * v2.y - v1.y * v2.x;

	return *this;
}

// ===========================================================================
// Name.......: Magnitude()
// Description:	This function normalizes the vector.
// Parameters.: NIL
// Returns....: NIL
// ===========================================================================
void Vector3d::Normalize(void)
{
	float c;

	c = Magnitude();

	if (c == 0.0)
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}
	else
	{
		x = x / c;
		y = y / c;
		z = z / c;
	}
}

// ===========================================================================
// Name.......: operator - ()
// Description:	This function returns the difference of two vectors.
// Parameters.: vecB			- the second vector
// Returns....: Vector3d			- the difference
// ===========================================================================
Vector3d Vector3d::operator-(const Vector3d &vecB) const
{
	Vector3d diff;

	diff.x = x - vecB.x;
	diff.y = y - vecB.y;
	diff.z = z - vecB.z;

	return diff;
}
/*
Vector3d Vector3d::operator - (const Vector3d &ptB) const
{
Vector3d diff;

	diff.x = x - ptB.x;
	diff.y = y - ptB.y;
	diff.z = z - ptB.z;

	return diff;
}
*/

// ===========================================================================
// Name.......: operator + ()
// Description:	This function returns the difference of two vectors.
// Parameters.: vecB			- the second vector
// Returns....: Vector3d			- the difference
// ===========================================================================
Vector3d Vector3d::operator+(const Vector3d &vecB) const
{
	Vector3d res;

	res.x = x + vecB.x;
	res.y = y + vecB.y;
	res.z = z + vecB.z;

	return res;
}
/*
Vector3d Vector3d::operator + (const Vector3d &ptB) const
{
Vector3d res;

	res.x = x + ptB.x;
	res.y = y + ptB.y;
	res.z = z + ptB.z;

	return res;
}
*/
// ===========================================================================
// Name.......: operator * ()
// Description:	This function returns the product of a vector multiplied by a
//				scalar.
// Parameters.: fScalar			- the scalar
// Returns....: Vector3d			- the product
// ===========================================================================
Vector3d Vector3d::operator*(const float fScalar) const
{
	Vector3d res;

	res.x = x * fScalar;
	res.y = y * fScalar;
	res.z = z * fScalar;

	return res;
}

// ===========================================================================
// Name.......: operator * ()
// Description:	This function returns the product of two vectors.
// Parameters.: vecB			- the second vector
// Returns....: Vector3d			- the product
// ===========================================================================
Vector3d Vector3d::operator*(const Vector3d &vecB) const
{
	Vector3d product;

	product.x = x * vecB.x;
	product.y = y * vecB.y;
	product.z = z * vecB.z;

	return product;
}

Vector3d Vector3d::operator/(const Vector3d &vecB) const
{
	Vector3d result;

	result.x = x / vecB.x;
	result.y = y / vecB.y;
	result.z = z / vecB.z;

	return result;
}

// ===========================================================================
// Name.......: operator = ()
// Description:	This function Sets the vector equal to another.
// Parameters.: vecB			- the vector
// Returns....: Vector3d			- the result
// ===========================================================================
Vector3d Vector3d::operator=(const Vector3d &vecB)
{
	x = vecB.x;
	y = vecB.y;
	z = vecB.z;

	return *this;
}
/*
// ===========================================================================
// Name.......: operator = ()
// Description:	This function Sets the vector equal to the value of a point.
// Parameters.: ptB				- the point
// Returns....: Vector3d			- the result
// ===========================================================================
Vector3d Vector3d::operator= (Vector3d ptB)
{
	x = ptB.x;
	y = ptB.y;
	z = ptB.z;

	return *this;
}
*/
// ===========================================================================
// Name.......: Unit()
// Description:	This function makes the vector the identity vector.
// Parameters.: NIL
// Returns....: NIL
// ===========================================================================
void Vector3d::Unit()
{
	// Initialize vector
	x = 0;
	y = 0;
	z = 0;
}

Vector3d Vector3d::GetPoint3d()
{
	Vector3d tmp;

	tmp.x = x;
	tmp.y = y;
	tmp.z = z;

	return tmp;
}

void Vector3d::Set(float xValue, float yValue, float zValue)
{
	x = xValue;
	y = yValue;
	z = zValue;
}

void Vector3d::SetX(float xValue)
{
	x = xValue;
}

void Vector3d::SetY(float yValue)
{
	y = yValue;
}

void Vector3d::SetZ(float zValue)
{
	z = zValue;
}

float Vector3d::GetX()
{
	return x;
}

float Vector3d::GetY()
{
	return y;
}

float Vector3d::GetZ()
{
	return z;
}

// ===========================================================================
// Name.......: Dot()
// Description:	This function is the constructor for Vec3D
// Parameters.: vecA			- the first vector
//				vecB			- the second vector
// Returns....: Vec3D			- the dot product
// ===========================================================================

float Vector3d::Dot(const Vector3d vecB) const
{
	float d;

	d = x * vecB.x;
	d += y * vecB.y;
	d += z * vecB.z;

	return (d);
}

// ===========================================================================
// Name.......: Cross()
// Description:	This function returns the cross product of two vectors.
// Parameters.: vecA			- the first vector
//				vecB			- the second vector
// Returns....: Vec3D			- the cross product
// ===========================================================================

Vector3d Vector3d::Cross(const Vector3d vecB) const
{
	Vector3d res;

	res.x = y * vecB.z - z * vecB.y;
	res.y = z * vecB.x - x * vecB.z;
	res.z = x * vecB.y - y * vecB.x;

	return res;
}

void Vector3d::Clip()
{
	if (x > 1.0)
		x = 1.0;
	if (x < 0.0)
		x = 0.0;
	if (y > 1.0)
		y = 1.0;
	if (y < 0.0)
		y = 0.0;
	if (z > 1.0)
		z = 1.0;
	if (z < 0.0)
		z = 0.0;
}

Vector3d Vector3d::GetNormalized() const
{
	Vector3d result(*this);

	result.Normalize();

	return result;
}

Vector3d Vector3d::GetRotatedX(float angle) const
{
	if (angle == 0.0)
		return (*this);

	float sinAngle = (float)sin(M_PI * angle / 180);
	float cosAngle = (float)cos(M_PI * angle / 180);

	return Vector3d(x,
					y * cosAngle - z * sinAngle,
					y * sinAngle + z * cosAngle);
}

void Vector3d::RotateX(float angle)
{
	(*this) = GetRotatedX(angle);
}

Vector3d Vector3d::GetRotatedY(float angle) const
{
	if (angle == 0.0)
		return (*this);

	float sinAngle = (float)sin(M_PI * angle / 180);
	float cosAngle = (float)cos(M_PI * angle / 180);

	return Vector3d(x * cosAngle + z * sinAngle,
					y,
					-x * sinAngle + z * cosAngle);
}

void Vector3d::RotateY(float angle)
{
	(*this) = GetRotatedY(angle);
}

Vector3d Vector3d::GetRotatedZ(float angle) const
{
	if (angle == 0.0)
		return (*this);

	float sinAngle = (float)sin(M_PI * angle / 180);
	float cosAngle = (float)cos(M_PI * angle / 180);

	return Vector3d(x * cosAngle - y * sinAngle,
					x * sinAngle + y * cosAngle,
					z);
}

void Vector3d::RotateZ(float angle)
{
	(*this) = GetRotatedZ(angle);
}

Vector3d Vector3d::GetRotatedAxis(float angle, const Vector3d &axis) const
{
	if (angle == 0.0)
		return (*this);

	Vector3d u = axis.GetNormalized();

	Vector3d rotMatrixRow0, rotMatrixRow1, rotMatrixRow2;

	float sinAngle = (float)sin(M_PI * angle / 180);
	float cosAngle = (float)cos(M_PI * angle / 180);
	float oneMinusCosAngle = 1.0f - cosAngle;

	rotMatrixRow0.x = (u.x) * (u.x) + cosAngle * (1 - (u.x) * (u.x));
	rotMatrixRow0.y = (u.x) * (u.y) * (oneMinusCosAngle)-sinAngle * u.z;
	rotMatrixRow0.z = (u.x) * (u.z) * (oneMinusCosAngle) + sinAngle * u.y;

	rotMatrixRow1.x = (u.x) * (u.y) * (oneMinusCosAngle) + sinAngle * u.z;
	rotMatrixRow1.y = (u.y) * (u.y) + cosAngle * (1 - (u.y) * (u.y));
	rotMatrixRow1.z = (u.y) * (u.z) * (oneMinusCosAngle)-sinAngle * u.x;

	rotMatrixRow2.x = (u.x) * (u.z) * (oneMinusCosAngle)-sinAngle * u.y;
	rotMatrixRow2.y = (u.y) * (u.z) * (oneMinusCosAngle) + sinAngle * u.x;
	rotMatrixRow2.z = (u.z) * (u.z) + cosAngle * (1 - (u.z) * (u.z));

	return Vector3d(this->Dot(rotMatrixRow0),
					this->Dot(rotMatrixRow1),
					this->Dot(rotMatrixRow2));
}

void Vector3d::RotateAxis(float angle, const Vector3d &axis)
{
	(*this) = GetRotatedAxis(angle, axis);
}

double Vector3d::AngleBetweenVectors(const Vector3d &vector2)
{
	// Remember, above we said that the Dot Product of returns the cosine of the angle
	// between 2 vectors?  Well, that is assuming they are unit vectors (normalize vectors).
	// So, if we don't have a unit vector, then instead of just saying  arcCos(DotProduct(A, B))
	// We need to divide the dot product by the magnitude of the 2 vectors multiplied by each other.
	// Here is the equation:   arc cosine of (V . W / || V || * || W || )
	// the || V || means the magnitude of V.  This then cancels out the magnitudes dot product magnitudes.
	// But basically, if you have normalize vectors already, you can forget about the magnitude part.

	// Get the dot product of the vectors
	float dotProduct = this->Dot(vector2);

	// Get the product of both of the vectors magnitudes
	float vectorsMagnitude = this->Magnitude() * vector2.Magnitude();

	// Get the arc cosine of the (dotProduct / vectorsMagnitude) which is the angle in RADIANS.
	// (IE.   PI/2 radians = 90 degrees      PI radians = 180 degrees    2*PI radians = 360 degrees)
	// To convert radians to degress use this equation:   radians * (PI / 180)
	// TO convert degrees to radians use this equation:   degrees * (180 / PI)
	double angle = acos(dotProduct / vectorsMagnitude);

	// Here we make sure that the angle is not a -1.#IND0000000 number, which means indefinate.
	// acos() thinks it's funny when it returns -1.#IND0000000.  If we don't do this check,
	// our collision results will sometimes say we are colliding when we aren't.  I found this
	// out the hard way after MANY hours and already wrong written tutorials :)  Usually
	// this value is found when the dot product and the maginitude are the same value.
	// We want to return 0 when this happens.
	//	if (_isnan(angle))
	if (isnan(angle))
		return 0;

	// Return the angle in radians
	return (angle);
}

void Vector3d::SetLength(const float l)
{
	float len = (*this).GetLength();
	if (len != 0.0f)
		(*this) *= l / len;
}

bool Vector3d::IsZero(void)
{
	if (((*this).x == 0.0f) && ((*this).y == 0.0f) && ((*this).z == 0.0f))
		return true;
	return false;
}

Vector3d Vector3d::GetMins(const Vector3d pVector)
{
	Vector3d result;

	result = pVector;

	if (x < result.x)
		result.x = x;
	if (y < result.y)
		result.y = y;
	if (z < result.z)
		result.z = z;

	return result;
}

Vector3d Vector3d::GetMaxes(const Vector3d pVector)
{
	Vector3d result;

	result = pVector;

	if (x > result.x)
		result.x = x;
	if (y > result.y)
		result.y = y;
	if (z > result.z)
		result.z = z;

	return result;
}
