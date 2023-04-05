

#include "math/Matrix3d.h"
#include "math/Math3d.h"
#include "math/MathCommons.h"

Matrix3d::Matrix3d()
{
    unit();
}

Matrix3d::~Matrix3d()
{
}

// ===========================================================================
// Name.......: unit()
// Description:	This function initializes a matrix.
// Parameters.: NIL
// Returns....: NIL
// ===========================================================================
void Matrix3d::unit()
{

    m11 = 1.0;
    m12 = 0;
    m13 = 0;
    m14 = 0;

    m21 = 0;
    m22 = 1.0;
    m23 = 0;
    m24 = 0;

    m31 = 0;
    m32 = 0;
    m33 = 1.0;
    m34 = 0;

    m41 = 0;
    m42 = 0;
    m43 = 0;
    m44 = 1.0;
}

/*

// ===========================================================================
// Name.......: operator=()
// Description:	This function is the copy assignment.
// Parameters.: rhs					- right hand side
// Returns....: NIL
// ===========================================================================
CMd2Model&
CMd2Model::operator= (const CMd2Model& rhs)
{
    int i;
    int j;

    if (this != &rhs)
    {
        if (m_num_frames != 0)
        {
            m_num_frames = 0;

            for (i=0; i < m_num_frames; i++)
            {
                delete [] m_framelist[i].tris;
            }

            delete [] m_points;
            delete [] m_framelist;
            delete [] m_tri_index;
            delete [] m_normals;
            delete [] m_texture_st;
        }

        strcpy (m_modelname, rhs.m_modelname);
        strcpy (m_skinname, rhs.m_skinname);

        m_skinwidth = rhs.m_skinwidth;
        m_skinheight = rhs.m_skinheight;
        m_framesize = rhs.m_framesize;

        m_num_skins = rhs.m_num_skins;
        m_num_xyz = rhs.m_num_xyz;
        m_num_st = rhs.m_num_st;
        m_num_tris = rhs.m_num_tris;
        m_num_frames = rhs.m_num_frames;

        // skin names
        if (m_num_skins)
        {
            for (i=0; i < m_num_skins; i++)
            {
                strcpy (m_skins[i], rhs.m_skins[i]);
            }
        }

        // texture coordinates (dstvert_t)
        m_texture_st = new dstvert_t[m_num_st];
        memcpy (m_texture_st, rhs.m_texture_st, sizeof (dstvert_t) * m_num_st);

        // triangle array indexes
        m_tri_index = new dtriangle_t[m_num_tris];
        m_normals = new Vec3D[m_num_tris];
        memcpy (m_tri_index, rhs.m_tri_index, sizeof(dtriangle_t) * m_num_tris);
        m_framelist = new framelist_t[m_num_frames];
        m_points = new POINT_3D[m_num_xyz];

        // triangle vertices
        for (i=0; i < m_num_frames; i++)
        {
            m_framelist[i].tris = new POINT_3D[m_num_xyz];

            for (j=0; j < m_num_xyz; j++)
            {
                m_framelist[i].tris[j].x = rhs.m_framelist[i].tris[j].x;
                m_framelist[i].tris[j].y = rhs.m_framelist[i].tris[j].y;
                m_framelist[i].tris[j].z = rhs.m_framelist[i].tris[j].z;
            }
        }

        m_pcxTex = rhs.m_pcxTex;
    }

    return *this;
} // operator=


*/

/*
// ===========================================================================
// Name.......: scale()
// Description:	This function scales all dimensions by scale factor.
// Parameters.: scale_factor		- the scale factor
// Returns....: NIL
// ===========================================================================
Matrix3D::scaleF ( double scale_factor)
{

Matrix3D	scale ;

    scale		= new Matrix3D() ;

    scale.m11	= scale_factor ;
    scale.m22	= scale_factor ;
    scale.m33	= scale_factor ;
    scale.m44	= 1 ;

    this.mulM ( scale ) ;
}
*/

// ===========================================================================
// Name.......: operator * ()
// Description:	This function multiples two matrices
// Parameters.: matB			- the second matrix
// Returns....: Matrix3D		- the product of the mulitplication
// ===========================================================================
Matrix3d Matrix3d::operator*(Matrix3d &matB)
{

    m11 = m11 * matB.m11 +
          m21 * matB.m12 +
          m31 * matB.m13 +
          m41 * matB.m14;
    m12 = m12 * matB.m11 +
          m22 * matB.m12 +
          m32 * matB.m13 +
          m42 * matB.m14;
    m13 = m13 * matB.m11 +
          m23 * matB.m12 +
          m33 * matB.m13 +
          m43 * matB.m14;
    m14 = m14 * matB.m11 +
          m24 * matB.m12 +
          m34 * matB.m13 +
          m44 * matB.m14;

    m21 = m11 * matB.m21 +
          m21 * matB.m22 +
          m31 * matB.m23 +
          m41 * matB.m24;
    m22 = m12 * matB.m21 +
          m22 * matB.m22 +
          m32 * matB.m23 +
          m42 * matB.m24;
    m23 = m13 * matB.m21 +
          m23 * matB.m22 +
          m33 * matB.m23 +
          m43 * matB.m24;
    m24 = m14 * matB.m21 +
          m24 * matB.m22 +
          m34 * matB.m23 +
          m44 * matB.m24;

    m31 = m11 * matB.m31 +
          m21 * matB.m32 +
          m31 * matB.m33 +
          m41 * matB.m34;
    m32 = m12 * matB.m31 +
          m22 * matB.m32 +
          m32 * matB.m33 +
          m42 * matB.m34;
    m33 = m13 * matB.m31 +
          m23 * matB.m32 +
          m33 * matB.m33 +
          m43 * matB.m34;
    m34 = m14 * matB.m31 +
          m24 * matB.m32 +
          m34 * matB.m33 +
          m44 * matB.m34;

    m41 = m11 * matB.m41 +
          m21 * matB.m42 +
          m31 * matB.m43 +
          m41 * matB.m44;
    m42 = m12 * matB.m41 +
          m22 * matB.m42 +
          m32 * matB.m43 +
          m42 * matB.m44;
    m43 = m13 * matB.m41 +
          m23 * matB.m42 +
          m33 * matB.m43 +
          m43 * matB.m44;
    m44 = m14 * matB.m41 +
          m24 * matB.m42 +
          m34 * matB.m43 +
          m44 * matB.m44;

    return *this;
}

// ===========================================================================
// Name.......: scale()
// Description:	This function scales all dimensions by scale factor.
// Parameters.: scale_factor		- the scale factor
// Returns....: NIL
// ===========================================================================
void Matrix3d::scale(double scale_factor)
{
    m11 *= scale_factor;
    m12 *= scale_factor;
    m13 *= scale_factor;
    m14 *= scale_factor;

    m21 *= scale_factor;
    m22 *= scale_factor;
    m23 *= scale_factor;
    m24 *= scale_factor;

    m31 *= scale_factor;
    m32 *= scale_factor;
    m33 *= scale_factor;
    m34 *= scale_factor;
}

// ===========================================================================
// Name.......: scale()
// Description:	This function scales scales along each axis independently.
// Parameters.: xTheta			- the scale factor along the x axis
//				yTheta			- the scale factor along the y axis
//				zTheta			- the scale factor along the z axis
// Returns....: NIL
// ===========================================================================
void Matrix3d::scale(double xTheta, double yTheta, double zTheta)
{
    m11 *= xTheta;
    m12 *= xTheta;
    m13 *= xTheta;
    m14 *= xTheta;

    m21 *= yTheta;
    m22 *= yTheta;
    m23 *= yTheta;
    m24 *= yTheta;

    m31 *= zTheta;
    m32 *= zTheta;
    m33 *= zTheta;
    m34 *= zTheta;
}

// ===========================================================================
// Name.......: translate()
// Description:	This function translates the origin.
// Parameters.: xTheta			- the amount to translate the x axis
//				yTheta			- the amount to translate the y axis
//				zTheta			- the amount to translate the z axis
// Returns....: NIL
// ===========================================================================
void Matrix3d::translate(double xTheta, double yTheta, double zTheta)
{
    m41 += xTheta;
    m42 += yTheta;
    m43 += zTheta;
}

void Matrix3d::translate(Vector3d delta_pos)
{
    m41 += delta_pos.x;
    m42 += delta_pos.y;
    m43 += delta_pos.z;
}

// ===========================================================================
// Name.......: xrot()
// Description:	This function rotates about the x axis.
// Parameters.: theta			- the amount to rotate about the x axis
// Returns....: NIL
// ===========================================================================
void Matrix3d::xrot(unsigned int theta)
{
    double fCos, fSin;
    double temp21, temp22, temp23, temp24;
    double temp31, temp32, temp33, temp34;

    fCos = Cos(theta);
    fSin = Sin(theta);

    temp21 = m21 * fCos + m31 * fSin;
    temp22 = m22 * fCos + m32 * fSin;
    temp23 = m23 * fCos + m33 * fSin;
    temp24 = m24 * fCos + m34 * fSin;

    temp31 = m31 * fCos - m21 * fSin;
    temp32 = m32 * fCos - m22 * fSin;
    temp33 = m33 * fCos - m23 * fSin;
    temp34 = m34 * fCos - m24 * fSin;

    m21 = temp21;
    m22 = temp22;
    m23 = temp23;
    m24 = temp24;

    m31 = temp31;
    m32 = temp32;
    m33 = temp33;
    m34 = temp34;
}

// ===========================================================================
// Name.......: yrot()
// Description:	This function rotates about the y axis.
// Parameters.: theta			- the amount to rotate about the y axis
// Returns....: NIL
// ===========================================================================
void Matrix3d::yrot(unsigned int theta)
{
    double fCos, fSin;
    double temp11, temp12, temp13, temp14;
    double temp31, temp32, temp33, temp34;

    fCos = Cos(theta);
    fSin = Sin(theta);

    temp11 = m11 * fCos + m31 * fSin;
    temp12 = m12 * fCos + m32 * fSin;
    temp13 = m13 * fCos + m33 * fSin;
    temp14 = m14 * fCos + m34 * fSin;

    temp31 = m31 * fCos - m11 * fSin;
    temp32 = m32 * fCos - m12 * fSin;
    temp33 = m33 * fCos - m13 * fSin;
    temp34 = m34 * fCos - m14 * fSin;

    m11 = temp11;
    m12 = temp12;
    m13 = temp13;
    m14 = temp14;

    m31 = temp31;
    m32 = temp32;
    m33 = temp33;
    m34 = temp34;
}

// ===========================================================================
// Name.......: zrot()
// Description:	This function rotates about the z axis.
// Parameters.: theta			- the amount to rotate about the z axis
// Returns....: NIL
// ===========================================================================
void Matrix3d::zrot(unsigned int theta)
{
    double fCos, fSin;
    double temp11, temp12, temp13, temp14;
    double temp21, temp22, temp23, temp24;

    fCos = Cos(theta);
    fSin = Sin(theta);

    temp11 = m11 * fCos - m21 * fSin;
    temp12 = m12 * fCos - m22 * fSin;
    temp13 = m13 * fCos - m23 * fSin;
    temp14 = m14 * fCos - m24 * fSin;

    temp21 = m21 * fCos + m11 * fSin;
    temp22 = m22 * fCos + m12 * fSin;
    temp23 = m23 * fCos + m13 * fSin;
    temp24 = m24 * fCos + m14 * fSin;

    m11 = temp11;
    m12 = temp12;
    m13 = temp13;
    m14 = temp14;

    m21 = temp21;
    m22 = temp22;
    m23 = temp23;
    m24 = temp24;
}

// ===========================================================================
// Name.......: transform()
// Description:	This function multiplies a point by a matrix.
// Parameters.: ptB				- 3D point
// Returns....: POINT_3D		- the resultant 3D point
// ===========================================================================
Vector3d Matrix3d::transform(const Vector3d &ptB)
{
    Vector3d result;

    result.x = m11 * ptB.x + m21 * ptB.y + m31 * ptB.z + m41; // m41 * 1
    result.y = m12 * ptB.x + m22 * ptB.y + m32 * ptB.z + m42; // m42 * 1
    result.z = m13 * ptB.x + m23 * ptB.y + m33 * ptB.z + m43; // m43 * 1

    return result;
}

// ===========================================================================
// Name.......: transform()
// Description:	This function multiplies a point by a matrix.
// Parameters.: ptB				- an array containing x, y and z components
// Returns....: POINT_3D		- the resultant 3D point
// ===========================================================================
Vector3d Matrix3d::transform(const float ptB[])
{
    Vector3d result;

    result.x = m11 * ptB[0] + m21 * ptB[1] + m31 * ptB[2] + m41; // m41 * 1
    result.y = m12 * ptB[0] + m22 * ptB[1] + m32 * ptB[2] + m42; // m42 * 1
    result.z = m13 * ptB[0] + m23 * ptB[1] + m33 * ptB[2] + m43; // m43 * 1

    return result;
}

void Matrix3d::rotateXYZ(unsigned int xTheta, unsigned int yTheta, unsigned int zTheta)
{

    yrot(yTheta);
    xrot(xTheta);
    zrot(zTheta);
}
