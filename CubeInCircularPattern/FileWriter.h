#pragma once
#include <string>
#include "Solid.h"

using namespace std;


class FileWriter
{
private :
	char header[80];
	char attribute[2];
	unsigned long noOfFacets;
	static int noOfCall;
	vector <Point> allVertices;
	vector <int> allFacets;
	 int findWhichVertex(Point toMatch, vector<Point> &vertices);
     int findWhichNormal(Point toMatch, vector<Point> &normals);

 public :
	 void writestlfile(Solid  &anySolid, int &noOfFacets, 
		               string &fileLocation,int &typeOfFile,
		               int &totalEdges,int noOfDivision=0);
};