#include <iostream>
# include "Point.h"
#include "Vector.h"

float Point::getX() const
	{
		return xCoord;
	}
float Point::getY() const
	{
		return yCoord;
	}
float Point::getZ() const
	{
		return zCoord;
	}

void Point::setX(float x)
{
	xCoord = x;
}
void Point::setY(float y)
{
	yCoord = y;
}
void Point::setZ(float z)
{
	zCoord = z;
}
