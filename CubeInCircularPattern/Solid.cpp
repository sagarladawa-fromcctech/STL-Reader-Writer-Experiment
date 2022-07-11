#include <iostream>
#include "Solid.h"

void Solid::showVerticesOfAllFacets(int &totalVertices) const// to show all the vectors 													  //  indicating the vertices of the solid
{
	cout <<endl<<"\t\t" <<"The  vertices for particular solid are"<<endl;
	cout << endl << "\t\t" << "x-coord" << "\t\t" << "y-coord" << "\t\t" << "z-coord" << endl << endl;
	for (int i = 0; i < totalVertices; i++)
	{
		cout <<"\t\t"<< solidVertices[i].getX() << "\t ";
		cout << "\t"<<solidVertices[i].getY() << "\t\t ";
		cout <<solidVertices[i].getZ() << endl<<endl<<endl;
	}
}
void Solid::showNormalsOfAllFacets(int &totalFacets) const // to show all	//  indicating the vertices of the solid
{
	cout <<endl<<"\t\t"<<"These is the normal data for the solid " << endl;
	cout <<endl<< "\t\t" << "i-coeff" << "\t\t" << "j-coeff" << "\t\t" << "k-coeff" << endl<<endl;
	for (int i = 0; i < totalFacets; i++)
	{
		cout <<"\t\t"<< solidNormals[i].getX() << "\t ";
		cout << "\t"<<solidNormals[i].getY() << "\t ";
		cout << "\t"<<solidNormals[i].getZ() << endl<<endl<<endl;
	}
}

void Solid::setFacetVertex(Point &corner)
{
	this->solidVertices.push_back(corner);
}

void Solid::setFacetNormal(Point &normal)
{
	this->solidNormals.push_back(normal);
}

Point Solid::getFacetVertex(int index) const
{
	return (this->solidVertices[index]);
}
Point Solid::getFacetNormal(int index) const
{
	return (this->solidNormals[index]);
}

int Solid::noOfNormals()
{
	return solidNormals.size();
}
int Solid::noOfVertices()
{
	return solidVertices.size();
}
