
#include "math/Vector4d.h"

void Vector4d::RotateX(float angle)
{
	(*this) = GetRotatedX(angle);
}

Vector4d Vector4d::GetRotatedX(float angle) const
{
	Vector3d v3d(x, y, z);

	v3d.RotateX(angle);

	return Vector4d(v3d.x, v3d.y, v3d.z, w);
}

void Vector4d::RotateY(float angle)
{
	(*this) = GetRotatedY(angle);
}

Vector4d Vector4d::GetRotatedY(float angle) const
{
	Vector3d v3d(x, y, z);

	v3d.RotateY(angle);

	return Vector4d(v3d.x, v3d.y, v3d.z, w);
}

void Vector4d::RotateZ(float angle)
{
	(*this) = GetRotatedZ(angle);
}

Vector4d Vector4d::GetRotatedZ(float angle) const
{
	Vector3d v3d(x, y, z);

	v3d.RotateZ(angle);

	return Vector4d(v3d.x, v3d.y, v3d.z, w);
}

void Vector4d::RotateAxis(float angle, const Vector3d &axis)
{
	(*this) = GetRotatedAxis(angle, axis);
}

Vector4d Vector4d::GetRotatedAxis(float angle, const Vector3d &axis) const
{
	Vector3d v3d(x, y, z);

	v3d.RotateAxis(angle, axis);

	return Vector4d(v3d.x, v3d.y, v3d.z, w);
}

Vector4d operator*(float scaleFactor, const Vector4d &rhs)
{
	return rhs * scaleFactor;
}

bool Vector4d::operator==(const Vector4d &rhs) const
{
	if (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w)
		return true;

	return false;
}

Vector4d::operator Vector3d()
{
	if (w == 0.0f || w == 1.0f)
		return Vector3d(x, y, z);
	else
		return Vector3d(x / w, y / w, z / w);
}
