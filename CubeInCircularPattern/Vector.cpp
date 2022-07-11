#include <iostream>
#include "Vector.h"

void Vector::setVectorCoefficients(float &value)
{
	this->vectorCoefficients.push_back(value);
}
void Vector::rotateVector(Vector &userVector, Vector &normalToUserVector, float angle)
{
	//[TODO #1] : Write your function here, to rotate a vector by a given angle.
}
void Vector::findUnitVector()
{
	//[TODO #1] : Write your function here, to find unit vector.
}
Vector Vector::crossProduct(Vector& one,Vector &two)
{
	//[TODO #1] : Write your function here, to return a vector which is a cross product of two vectors.
}

Vector Vector ::operator*(float & radius)
{
	Vector newVector;
	for (int i = 0; i < 3; i++)
	{
		newVector.vectorCoefficients.push_back(this->vectorCoefficients[i] * radius);
	}
	return newVector;
}

Point Vector::operator +(Point &anyCorner)
{
	Point newPoint;
	newPoint.setX(anyCorner.getX() + this->vectorCoefficients[0]);
	newPoint.setY(anyCorner.getY() + this->vectorCoefficients[1]);
	newPoint.setZ(anyCorner.getZ() + this->vectorCoefficients[2]);
	return newPoint;
}
