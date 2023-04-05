#pragma once

#include <math.h>

class Matrix3d;

//==============================================================================
// Vector 3D
class Vector3d
{
public:
	float x, y, z;

	Vector3d();
	Vector3d(const float ptAX, const float ptAY, const float ptAZ);

	static Vector3d Zero() { return Vector3d(0, 0, 0); }
	static Vector3d One() { return Vector3d(1, 1, 1); }

	Vector3d DiffPt(Vector3d ptA, Vector3d ptB);
	double Magnitude(void) const;
	double GetLength(void) const
	{
		return (double)sqrt((x * x) + (y * y) + (z * z));
	}

	float GetSquaredLength(void) const
	{
		return (float)(x * x) + (y * y) + (z * z);
	}

	Vector3d NormalPt(Vector3d ptA, Vector3d ptB, Vector3d ptC);
	void Normalize(void);
	Vector3d GetNormalized() const;

	Vector3d operator-(const Vector3d &vecB) const;
	Vector3d operator+(const Vector3d &vecB) const;
	Vector3d operator*(const float fScalar) const;
	friend Vector3d operator*(float fScalar, const Vector3d &rhs)
	{
		return rhs * fScalar;
	}

	Vector3d operator+(const float fScalar) const
	{
		return Vector3d(x + fScalar, y + fScalar, z + fScalar);
	}
	Vector3d operator-(const float fScalar) const
	{
		return Vector3d(x - fScalar, y - fScalar, z - fScalar);
	}

	Vector3d operator*(const Vector3d &vecB) const;
	Vector3d operator=(const Vector3d &vecB);
	Vector3d operator/(const Vector3d &vecB) const;

	// self-add etc
	void operator+=(const Vector3d &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
	}

	void operator-=(const Vector3d &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
	}

	void operator*=(const float rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
	}

	void operator/=(const float rhs)
	{
		if (rhs == 0.0f)
			return;
		else
		{
			x /= rhs;
			y /= rhs;
			z /= rhs;
		}
	}

	void operator/=(const Vector3d &rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
	}

	void operator*=(const Vector3d &rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
	}

	void Unit();

	Vector3d GetPoint3d();

	void Set(float xValue, float yValue, float zValue);

	void SetX(float xValue);
	void SetY(float yValue);
	void SetZ(float zValue);
	float GetX();
	float GetY();
	float GetZ();

	float Dot(const Vector3d vecB) const;
	Vector3d Cross(const Vector3d vecB) const;

	void Clip();

	// unary operators
	Vector3d operator-(void) const
	{
		return Vector3d(-x, -y, -z);
	}

	Vector3d operator+(void) const
	{
		return *this;
	}

	Vector3d operator/(const float rhs) const
	{
		return (rhs == 0.0f) ? Vector3d(0.0f, 0.0f, 0.0f) : Vector3d(x / rhs, y / rhs, z / rhs);
	}

	bool operator==(const Vector3d &rhs) const
	{
		if (x == rhs.x && y == rhs.y && z == rhs.z)
			return true;

		return false;
	}

	bool operator!=(const Vector3d &rhs) const
	{
		return !((*this) == rhs);
	}

	// rotations
	void RotateX(float angle);
	Vector3d GetRotatedX(float angle) const;
	void RotateY(float angle);
	Vector3d GetRotatedY(float angle) const;
	void RotateZ(float angle);
	Vector3d GetRotatedZ(float angle) const;

	void RotateAxis(float angle, const Vector3d &axis);
	Vector3d GetRotatedAxis(float angle, const Vector3d &axis) const;

	// linear interpolate
	Vector3d lerp(const Vector3d &v2, float factor) const
	{
		return (*this) * (1.0f - factor) + v2 * factor;
	}

	double AngleBetweenVectors(const Vector3d &vector2);

	// cast to pointer to a (float *) for glGetFloatv etc
	operator float *() const { return (float *)this; }
	operator const float *() const { return (const float *)this; }

	void SetLength(const float l);
	bool IsZero(void);

	Vector3d GetMins(const Vector3d pVector);
	Vector3d GetMaxes(const Vector3d pVector);

	inline bool operator<(const Vector3d &pVector) const
	{
		return ((x < pVector.x) &&
				(y < pVector.y) &&
				(z < pVector.z));
	}

	inline bool operator>(const Vector3d &pVector) const
	{
		return ((x > pVector.x) &&
				(y > pVector.y) &&
				(z > pVector.z));
	}
	/*
		inline bool operator == (const Vector3d pVector) const {
		  return ( (x == pVector.x) &&
				   (y == pVector.y) &&
				   (z == pVector.z) ) ;
		}

		inline bool operator != (const Vector3d pVector) const {
		  return ( (x != pVector.x) &&
				   (y != pVector.y) &&
				   (z != pVector.z) ) ;
		}
	*/
	inline bool operator<=(const Vector3d &pVector) const
	{
		return ((x <= pVector.x) &&
				(y <= pVector.y) &&
				(z <= pVector.z));
	}

	inline bool operator>=(const Vector3d &pVector) const
	{
		return ((x >= pVector.x) &&
				(y >= pVector.y) &&
				(z >= pVector.z));
	}
};

// void	Swap ( Vector3d pV1, Vector3d pV2 ) { Vector3d temp; temp = pV1; pV1=pV2; pV2=temp; } ;
