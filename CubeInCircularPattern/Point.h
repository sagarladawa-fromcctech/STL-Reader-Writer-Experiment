#pragma once

#include <vector>
using namespace std;

class Point
{
private :
	float xCoord, yCoord, zCoord;
public :
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	float getX()const;
	float getY()const;
	float getZ()const;
};

