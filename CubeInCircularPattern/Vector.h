#pragma once

#include <vector>

using namespace std;

class Vector
{
 private :
	vector <float> vectorCoefficients;
 public:
	void setVectorCoefficients(float &value);
	void rotateVector(Vector &userVector, Vector &normalToUserVector, float angle);
	void findUnitVector();
	static Vector crossProduct(Vector &one, Vector &two);
	Vector operator *(float &radius);
	Point operator +(Point &firstCorner);
};