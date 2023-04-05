
#include <stdio.h>

#include "math/Point2dList.h"

Point2dList::Point2dList()
{
	pointList = NULL;

	maxQty = MAX_POINTS2D;
	qty = 0;

	for (long i = 0; i < MAX_POINTS2D; i++)
	{
		flag[i][0] = '\0';
	}
}

Point2dList::~Point2dList()
{
	delete[] pointList;
}

void Point2dList::setMaxQty(long pMaxQty)
{
	delete[] pointList;
	maxQty = pMaxQty;
	qty = 0;
}

long Point2dList::addPoint(double x, double y)
{
	Point2d point;

	point.x = x;
	point.y = y;

	return addPoint(point);
}

long Point2dList::addPoint(Point2d point)
{
	/*
		if (qty<MAX_POINTS2D)
		{
			pointList [ qty ]	= point ;
			qty ++ ;
			return (qty-1) ;
		}
		else
			return -1 ;
	*/
	long n;
	Point2d *temp;

	if (qty < maxQty)
	{

		//	Resize the Array
		if (qty > 0)
		{
			temp = new Point2d[qty];

			for (n = 0; n < qty; n++)
				temp[n] = pointList[n];

			pointList = new Point2d[qty + 1];

			for (n = 0; n < qty; n++)
				pointList[n] = temp[n];

			delete[] temp;
			//
		}
		else
			pointList = new Point2d[1];

		pointList[qty] = point;
		qty++;

		return qty - 1;
	}
	else
		return -1;
}

Point2dList &Point2dList::operator=(const Point2dList &points)
{
	if (this == &points)
		return *this;
	delete[] pointList;

	pointList = new Point2d[points.getQty()];

	qty = points.getQty();

	for (long n = 0; n < qty; n++)
		pointList[n] = points.pointList[n];

	return *this;
}

/*
const GLfloat *	Point2dList::getPointGL( long idx ) const
{
GLfloat	point[2] ;

	point[0]	= (GLfloat)pointList[idx].x ;
	point[1]	= (GLfloat)pointList[idx].y ;

	return point ;
}
*/
