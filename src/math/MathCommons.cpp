
#include "math/MathCommons.h"

#include <math.h>

double CosTable[360];
double SinTable[360];

/*
	SIN	COS		        SIN + 90	COS + 90

0	0,0000	1,0000		1,0000	0,0000
15	0,2588	0,9659		0,9659	-0,2588
30	0,5000	0,8660		0,8660	-0,5000
45	0,7071	0,7071		0,7071	-0,7071
60	0,8660	0,5000		0,5000	-0,8660
75	0,9659	0,2588		0,2588	-0,9659
90	1,0000	0,0000		0,0000	-1,0000
105	0,9659	-0,2588		-0,2588	-0,9659
120	0,8660	-0,5000		-0,5000	-0,8660
135	0,7071	-0,7071		-0,7071	-0,7071
150	0,5000	-0,8660		-0,8660	-0,5000
165	0,2588	-0,9659		-0,9659	-0,2588
180	0,0000	-1,0000		-1,0000	0,0000
195	-0,2588	-0,9659		-0,9659	0,2588
210	-0,5000	-0,8660		-0,8660	0,5000
225	-0,7071	-0,7071		-0,7071	0,7071
240	-0,8660	-0,5000		-0,5000	0,8660
255	-0,9659	-0,2588		-0,2588	0,9659
270	-1,0000	0,0000		0,0000	1,0000
285	-0,9659	0,2588		0,2588	0,9659
300	-0,8660	0,5000		0,5000	0,8660
315	-0,7071	0,7071		0,7071	0,7071
330	-0,5000	0,8660		0,8660	0,5000
345	-0,2588	0,9659		0,9659	0,2588

*/

//==============================================================================
// Helper Math Functions

// ===========================================================================
// Name.......: Initialize_CosSin()
// Description:	This function initializes the sine and cosine lookup tables.
// Parameters.: NIL
// Returns....: NIL
// ===========================================================================
void Initialize_CosSin()
{
	int i;

	for (i = 0; i < 360; i++)
	{
		CosTable[i] = cos(M_PI / 180.0 * i);
	}

	for (i = 0; i < 360; i++)
	{
		SinTable[i] = sin(M_PI / 180.0 * i);
	}
}

// ===========================================================================
// Name.......: Sin()
// Description:	This function returns the sine of an angle.
// Parameters.: Angle			- the given angle
// Returns....: double			- the sine of the angle
// ===========================================================================

double Sin(unsigned int Angle)
{

	return SinTable[Angle];
}

double Sin(float Angle)
{

	return SinTable[(unsigned int)Angle];
}

// ===========================================================================
// Name.......: Cos()
// Description:	This function returns the cosine of an angle.
// Parameters.: Angle			- the given angle
// Returns....: double			- the cosine of the angle
// ===========================================================================

double Cos(unsigned int Angle)
{
	return CosTable[Angle];
}

double Cos(float Angle)
{
	return CosTable[(unsigned int)Angle];
}
