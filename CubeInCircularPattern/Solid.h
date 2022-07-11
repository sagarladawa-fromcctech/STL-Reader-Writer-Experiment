#pragma once
#include <vector>
#include "Point.h"

using namespace std;

class Solid
{	
private :
	vector <Point> solidVertices;
	vector <Point> solidNormals;

  public :
	  int noOfVertices();
	  int noOfNormals();

	  void setFacetVertex(Point &corner);
	  void setFacetNormal(Point &normal);
	
	  Point getFacetVertex(int index) const;
	  Point getFacetNormal(int index)const;
	
	  void showVerticesOfAllFacets(int &totalVertices)const;
	  void showNormalsOfAllFacets(int &totalFacets)const;
};

