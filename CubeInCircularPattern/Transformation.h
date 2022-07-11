#pragma once

#include "Solid.h"
#include "Vector.h"

using namespace std;

class Transformation
{
public :
	static Solid translateSolidVertexAlongVector(Solid &firstSolid, Vector  &unitVector,
		int &noOfvertices, int &noOfFacets, float &radius);

};

