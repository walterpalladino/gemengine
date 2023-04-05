
#pragma once


struct Point2d
{
public:
   float	x,
   			y;

	//cast to pointer to a (float *) for glGetFloatv etc
	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}

} ;


