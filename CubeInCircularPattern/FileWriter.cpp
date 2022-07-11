# include <iostream>
#include <vector>
#include <fstream>
#include "FileWriter.h"
#include "Solid.h"


void FileWriter::writestlfile(Solid  &anySolid, int &noOfFacets, 
	                               string &fileLocation,int &typeOfFile,
	                               int &totalEdges,int noOfDivision)
{
	string fileAddress;
	if (typeOfFile == 0)
	{
		int iter = 0;
		ofstream foutput;                                 // this function writes the data from the translated 
												 //  solids in the new STL File. 
		fileAddress = fileLocation + "solid.stl";
		foutput.open(fileAddress, ios::app);
		foutput << "solid ASCII" << endl;
		for (int s = 0; s < noOfFacets; s++) {
			foutput << "  facet normal " << anySolid.getFacetNormal(s).getX() << "\t" << anySolid.getFacetNormal(s).getY()
				<< "\t" << anySolid.getFacetNormal(s).getZ() << endl;
			foutput << "    outer loop" << endl;
			for (int i = 0; i < 3; i++)
			{
				foutput << "      vertex" << "    " << anySolid.getFacetVertex(iter).getX() << " "
					<< anySolid.getFacetVertex(iter).getY() << " " << anySolid.getFacetVertex(iter).getZ() << endl;
				iter = iter + 1;
			}
			foutput << "    endloop" << endl;
			foutput << "  endfacet" << endl;
		}
		foutput << "endsolid " << endl;
		foutput.close();
		noOfCall++;
	}

	else if (typeOfFile == 1)
	{
		int iter = 0;
		string attrib = "0";
		ofstream foutput;   // this function writes the data from the translated solid												 //  solids in the new STL File. 
		fileAddress = fileLocation + "solid.stl";
		
		strncpy_s(header, fileAddress.c_str(), sizeof(header) - 1);
		this->noOfFacets = noOfFacets;
		strncpy_s(attribute,attrib.c_str(),sizeof(attribute)-1);

		foutput.open(fileAddress, ios::out | ios::app | ios::binary);
		if (noOfCall == 0)
		{
			foutput.write((char*)&this->header, sizeof(header));
			foutput.write((char*)&(this->noOfFacets), sizeof(this->noOfFacets));
		}
		vector <vector <float>> totalTriangle;
		vector <vector<float>> totalNormal;
		int cursor = 0;
		for (int i = 0; i < (noOfFacets*3); i++)
		{
			vector <float> triangle;
			Point corner = anySolid.getFacetVertex(i);
			triangle.push_back(corner.getX());
			triangle.push_back(corner.getY());
			triangle.push_back(corner.getZ());

			totalTriangle.push_back(triangle);
		}

		for (int i = 0; i < noOfFacets; i++)
		{
			vector<float> normal;
			Point normals = anySolid.getFacetNormal(i);
		     normal.push_back(normals.getX());
			 normal.push_back(normals.getY());
			 normal.push_back(normals.getZ());
			 totalNormal.push_back(normal);
		}

		for (int i = 0; i < totalNormal.size(); i++)
		{
			
				foutput.write((char*)&totalNormal[i][0], sizeof(totalNormal[i][0]));
				foutput.write((char*)&totalNormal[i][1], sizeof(totalNormal[i][1]));
				foutput.write((char*)&totalNormal[i][2], sizeof(totalNormal[i][2]));

				for (int j=0;j<3;j++)
				{
					foutput.write((char*)&totalTriangle[iter][0], sizeof(totalTriangle[iter][0]));
					foutput.write((char*)&totalTriangle[iter][1], sizeof(totalTriangle[iter][1]));
					foutput.write((char*)&totalTriangle[iter][2], sizeof(totalTriangle[iter][2]));
					iter++;
				}
				foutput.write((char*)&this->attribute, sizeof(attribute));
			
			
		}
		FileWriter::noOfCall++;
		foutput.close();
	}

	else if (typeOfFile == 2)
	{
		vector <Point> vertices;
		vector <Point> normals;
		ofstream fout;
		fileAddress = fileLocation + "solid.obj";
		fout.open(fileAddress,ios::app);

		for (int i = 0; (i < noOfFacets * 3); i++)
		{
			int count = 1;
			Point vertex;
			if (i == 0)
			{
				vertex = anySolid.getFacetVertex(i);
				vertices.push_back(vertex);
			}
			else
			{
				vertex = anySolid.getFacetVertex(i);
				for (int j = 0; j < vertices.size(); j++)
				{
					if (vertex.getX() == vertices[j].getX() && vertex.getY() == vertices[j].getY()
						&& vertex.getZ() == vertices[j].getZ())
					{
						count++;
						continue;
					}
				}
				if (count == 1)
				{
					vertices.push_back(vertex);
				}
			}

		}
		for (int i = 0; (i < noOfFacets); i++)
		{
			int count = 1;
			Point normal;
			if (i == 0)
			{
				normal = anySolid.getFacetNormal(i);
				normals.push_back(normal);
			}
			else
			{
				normal = anySolid.getFacetNormal(i);
				for (int j = 0; j < normals.size(); j++)
				{
					if (normal.getX() == normals[j].getX() && normal.getY() == normals[j].getY()
						&& normal.getZ() == normals[j].getZ())
					{
						count++;
						continue;
					}
				}
				if (count == 1)
				{
					normals.push_back(normal);
				}
			}

		}
			fout << "o cube" << endl << endl;
		
		for (int i = 0; i < vertices.size(); i++)
		{
			fout << "v " << vertices[i].getX() << "\t" << vertices[i].getY() << "\t" <<
				vertices[i].getZ() << endl;
		}
		fout << endl;
		for (int i = 0; i < normals.size(); i++)
		{
			fout << "vn " << normals[i].getX() << "\t" << normals[i].getY() << "\t" <<
				normals[i].getZ() << endl;
		}
		fout << endl;
		int iter = 0;
		for (int i = 0; i < noOfFacets; i++)
		{
			fout << "f "<<findWhichVertex(anySolid.getFacetVertex(iter),vertices)<<"//"
				<<findWhichNormal(anySolid.getFacetNormal(i),normals)<<"\t"
				<<findWhichVertex(anySolid.getFacetVertex((iter+1)),vertices) << "//"
				<< findWhichNormal(anySolid.getFacetNormal(i),normals) << "\t"
				<<findWhichVertex(anySolid.getFacetVertex(iter+2),vertices) << "//"
				<< findWhichNormal(anySolid.getFacetNormal(i),normals) << endl;
			iter=iter+3;
		}
		fout << endl;

		FileWriter::noOfCall++;
		fout.close();
	}

	

	else if (typeOfFile == 3)
	{
	
	 vector <Point> vertices;
	 fileAddress = fileLocation + "solid.off";
	 ofstream fout;
	 int iter = 0;
	 fout.open(fileAddress, ios::app);
	 for (int i = 0; (i < noOfFacets * 3); i++)
	 {
		 int count = 1;
		 Point vertex;
		 if (i == 0)
		 {
			 vertex = anySolid.getFacetVertex(i);
			 vertices.push_back(vertex);
		 }
		 else
		 {
			 vertex = anySolid.getFacetVertex(i);
			 for (int j = 0; j < vertices.size(); j++)
			 {
				 if (vertex.getX() == vertices[j].getX() && vertex.getY() == vertices[j].getY()
					 && vertex.getZ() == vertices[j].getZ())
				 {
					 count++;
					 continue;
				 }
			 }
			 if (count == 1)
			 {
				 vertices.push_back(vertex);
			 }
		 }
	 }
	 for (int i = 0; i < vertices.size(); i++)
	 {
		 FileWriter::allVertices.push_back(vertices[i]);
	 }

	 for (int i = 0; i < noOfFacets*3; i++)
	 {
		 allFacets.push_back(findWhichVertex(anySolid.getFacetVertex(i),vertices)-1);
	 }
	 
	 if (noOfCall == 0)
	 {
		 fout << "OFF" << endl << endl;
	 }
	 if (noOfCall== noOfDivision)
	 {
		 fout << FileWriter::allVertices.size() << " " 
			 <<noOfFacets*(noOfDivision+1) << " " << totalEdges*(noOfDivision+1) << endl;

		 for (int i = 0; i <allVertices.size(); i++)
		 {
			 fout << " " << allVertices[i].getX() << "\t" << allVertices[i].getY() << "\t" <<
				 allVertices[i].getZ() << endl;
		 }
		 for (int j = 0; j < FileWriter::allFacets.size(); j=j+3)
		 {
			 fout << "3" << " ";
			 fout << " " << allFacets[j] << "\t";
			 fout << " " << allFacets[j + 1] << "\t";
			 fout << " " << allFacets[j + 2] << "\t"<<endl;
		 }

		 fout << endl;
	 }
	 FileWriter::noOfCall++;
	 fout.close();
    }	
}
int FileWriter::noOfCall = 0;

int FileWriter::findWhichVertex(Point toMatch, vector <Point> &vertices)
{
	for (int i = 0; i < vertices.size(); i++)
	{
		if (toMatch.getX() == vertices[i].getX() && toMatch.getY() == vertices[i].getY() &&
			toMatch.getZ() == vertices[i].getZ())
		{
			return i + 1 + noOfCall * vertices.size();
		}
	}
}
int FileWriter::findWhichNormal(Point toMatch, vector <Point> &normals)
{
	for (int i = 0; i < normals.size(); i++)
	{
		if (toMatch.getX() == normals[i].getX() && toMatch.getY() == normals[i].getY() &&
			toMatch.getZ() == normals[i].getZ())
		{
			
			return i+1+noOfCall*6;
			
		}
	}
}
