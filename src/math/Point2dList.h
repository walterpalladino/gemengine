
#pragma once

// #include	<windows.h>
// #include	<windowsx.h>

#include <stdio.h>

// #include	<gl\gl.h>			// Header File For The OpenGL32 Library
// #include	<gl\glu.h>			// Header File For The GLu32 Library
// #include	<gl\glaux.h>		// Header File For The GLaux Library

#include "math/Point2d.h"

#define MAX_POINTS2D 1024

class Point2dList
{

private:
public:
	long qty;
	long maxQty;
	//	Point2d			pointList [ MAX_POINTS2D ] ;
	Point2d *pointList;
	char flag[MAX_POINTS2D][1];

	Point2dList();
	~Point2dList();

	long getQty() const { return qty; };
	void setMaxQty(long pMaxQty);

	long addPoint(Point2d point);
	long addPoint(double x, double y);

	//	const Point2d	getPoint( long idx ) const { return pointList[idx] ; } ;
	//	const GLfloat *	getPointGL( long idx ) const ;

	char getFlag(long idx) const { return flag[idx][0]; };
	void setFlag(long idx) { flag[idx][0] = 'X'; };
	void replace(long idx, Point2d point) { pointList[idx] = point; };

	//	Operators	Overloaded
	//	Point2dList & Point2dList::operator=(const Point2dList & points);
	Point2dList &operator=(const Point2dList &points);
};
