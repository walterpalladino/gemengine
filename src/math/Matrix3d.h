#pragma once

#include "math/Vector3d.h"

class Matrix3d
{

private:
	double m11, m12, m13, m14;
	double m21, m22, m23, m24;
	double m31, m32, m33, m34;
	double m41, m42, m43, m44;

public:
	Matrix3d();
	~Matrix3d();

	void unit();
	Matrix3d operator*(Matrix3d &matB);

	void scale(double scale_factor);
	void scale(double xTheta, double yTheta, double zTheta);
	void translate(Vector3d delta_pos);
	void translate(double x, double y, double z);
	void xrot(unsigned int theta);
	void yrot(unsigned int theta);
	void zrot(unsigned int theta);
	void rotateXYZ(unsigned int xTheta, unsigned int yTheta, unsigned int zTheta);

	Vector3d transform(const Vector3d &ptB);
	Vector3d transform(const float ptB[]);
};
