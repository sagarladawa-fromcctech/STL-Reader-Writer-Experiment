#pragma once

#include <string>
#include "Solid.h"

using namespace std;

class FileReader
{
private:
	struct Stl
	{
		char header[80];
		char noOfTriangle[4];
		unsigned long noOfFacets;
	};
	string iterateLine(ifstream &fin);
public :
	static int countNoOfWords(string &line);
	static void readTriangleData(char triangle[50],Point &normal,
		                             Point &vertex1,Point &vertex2,Point &vertex3);
	void calculateNoOfVerticesAndFacets(string &path, int &totalFacets, 
		                               int &totalVertices,int &typeOfFile,int &totalEdges);
	void StoreFileDataInObject(string &path, Solid &solid,int &typeOfFile);
};


