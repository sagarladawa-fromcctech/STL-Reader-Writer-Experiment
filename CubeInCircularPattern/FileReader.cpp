#include <fstream>
#include <sstream>
#include <iostream>
#include "String.h"
#include "Filereader.h"
#include "Point.h"
#include "Solid.h"

string FileReader::iterateLine(ifstream &fin)
{
	string line;
	getline(fin, line);
	return line;
}

void FileReader:: calculateNoOfVerticesAndFacets(string &path, int &totalFacets, int &totalVertices
	                                                  ,int &typeOfFile,int &totalEdges)
{
	if (typeOfFile == 0)
	{
		ifstream fin;
	    fin.open(path);
		string line;
		while (getline(fin, line))
		{
			line = String::trim(line);          // trim the blank spaces from left and right side of the line
			if (String::startsWith(line, "facet normal")) //check if the line starts with "facet normal"
			{
				totalFacets++;
			}
			if (String::startsWith(line, "vertex")) // check if the line starts with "vertex"
			{
				totalVertices++;
			}
		}
		fin.close();
	}
	else if (typeOfFile == 1)
	{
		Stl file;
		ifstream binaryFile;
		binaryFile.open(path,ios::in|ios::binary);
		
		binaryFile.read(file.header,sizeof(file.header));
		binaryFile.read(file.noOfTriangle, sizeof(file.noOfTriangle));
		file.noOfFacets = *((unsigned long *)file.noOfTriangle);
		totalFacets = file.noOfFacets;
		totalVertices = totalFacets * 3;
		binaryFile.close();
	}

	else if (typeOfFile == 2)
	{
		ifstream fin;
		fin.open(path);
		string line;
		while (getline(fin, line))
		{
			line = String::trim(line);          // trim the blank spaces from left and right side of the line
			if (String::startsWith(line, "f")) //check if the line starts with "facet normal"
			{
				int count = countNoOfWords(line);
				if(count==5)
				{
					totalFacets = totalFacets + 2;
				}
				if (count == 4)
				{
					totalFacets++;
				}
			}
		}
		totalVertices = totalFacets * 3;
		fin.close();
	}
	else if (typeOfFile==3)
	{
		ifstream fin;
		fin.open(path);
		string line;
		int noOfVertices;
		while (getline(fin, line))
		{
			line = String::trim(line);
			if (String::startsWith(line, "OFF"))
			{
				do
				{
					line = iterateLine(fin);
				} while (line.empty()||String::startsWith(line,"#"));
			
				string stringValues = line;
				istringstream iss(stringValues);
				string val;
				iss >> val;
				noOfVertices = stoi(val);
				iss >> val;
				iss >> val;
				totalEdges = stoi(val);
				int num = 0;
				while (num <= noOfVertices)
				{
					line = iterateLine(fin);
					num++;
				}

				while (!line.empty())
				{
					line = String::trim(line);
					if (String::startsWith(line, "4 "))
					{
						totalFacets = totalFacets + 2;
					}
					if (String::startsWith(line, "3 "))
					{
						totalFacets++;
					}
					line = iterateLine(fin);
				}
			}
		}
		totalVertices = totalFacets * 3;
	}
}

void FileReader::StoreFileDataInObject(string &path, Solid &solid, int &typeOfFile)
{
	if (typeOfFile == 0)
	{
		ifstream fin;
		string line;
		fin.open(path);
		while (getline(fin, line))
		{
			line = String::trim(line); // trim the blank spaces on left and right side of the line
			if (String::startsWith(line, "facet normal")) //check if the line starts with "facet normal"
			{
				string stringvalues = line;

				istringstream iss(stringvalues); // to break the line in words
				Point normal;
				for (int n = 0; n < 5; n++) // iterate through all the words from the line and store the requaired words
				{

					string val;
					iss >> val;
					if (n == 2)
					{
						normal.setX(stof(val)); // converting string to float and pushing in the solid
					}
					if (n == 3)
					{
						normal.setY(stof(val)); // converting string to float and pushing in the solid
					}
					if (n == 4)
					{
						normal.setZ(stof(val)); // converting string to float and pushing in the solid
					}

					//solid.solidNorm.push_back(normal);
				}
				solid.setFacetNormal(normal);
			}
			if (String::startsWith(line, "vertex")) //check if the line starts with "vertex"
			{
				string strings = line;
				istringstream iff(strings); // to break the line in words
				Point vertex;
				for (int n = 0; n < 4; n++)// iterate through all the words from the line and store the requaired words
				{

					string cal;
					iff >> cal;
					if (n == 1)
					{
						vertex.setX(stof(cal)); // converting string to float and pushing in the solid
					}
					if (n == 2)
					{
						vertex.setY(stof(cal)); // converting string to float and pushing in the solid
					}
					if (n == 3)
					{
						vertex.setZ(stof(cal)); // converting string to float and pushing in the solid
					}
				}
				solid.setFacetVertex(vertex);
			}
		}
		fin.close();
	}

	else if (typeOfFile == 1)
	{
		Stl file;
		ifstream binaryFile;
		int pos;
		binaryFile.open(path, ios::in | ios::binary);

		binaryFile.seekg(0, ios::end);
		pos = (int)binaryFile.tellg();
		int size = pos;
		binaryFile.seekg(0, ios::beg);

		binaryFile.read(file.header, sizeof(file.header));
		binaryFile.read(file.noOfTriangle, sizeof(file.noOfTriangle));
		while (binaryFile.tellg() < size)
		{
			char triangle[50];
			binaryFile.read(triangle, sizeof(triangle));
			Point normal;
			Point vertex1, vertex2, vertex3;

			readTriangleData(triangle, normal, vertex1, vertex2, vertex3);
			solid.setFacetVertex(vertex1);
			solid.setFacetVertex(vertex2);
			solid.setFacetVertex(vertex3);
			solid.setFacetNormal(normal);
		}
		binaryFile.close();
	}
	else if (typeOfFile == 2)
	{
		ifstream fin;
		string line;
		fin.open(path);

		vector <Point> vertices;
		vector<Point> normals;

		while (getline(fin, line))
		{
			line = String::trim(line); // trim the blank spaces on left and right side of the line
			if (String::startsWith(line, "v ")) //check if the line starts with "facet normal"
			{
				string stringvalues = line;
				istringstream iss(stringvalues); // to break the line in words

				Point vertex;
				for (int n = 0; n < 4; n++) // iterate through all the words from the line and store the requaired words
				{
					string val;
					iss >> val;
					if (n == 1)
					{
						vertex.setX(stof(val)); // converting string to float and pushing in the solid
					}
					if (n == 2)
					{
						vertex.setY(stof(val));
					}
					if (n == 3)
					{
						vertex.setZ(stof(val));
					}
				}
				vertices.push_back(vertex);
			}

			if (String::startsWith(line, "vn")) //check if the line starts with "facet normal"
			{
				string stringvalues = line;
				istringstream iss(stringvalues); // to break the line in words
				Point normal;
				for (int n = 0; n < 4; n++) // iterate through all the words from the line and store the requaired words
				{
					string val;
					iss >> val;
					if (n == 1)
					{
						normal.setX(stof(val)); // converting string to float and pushing in the solid
					}
					if (n == 2)
					{
						normal.setY(stof(val));
					}
					if (n == 3)
					{
						normal.setZ(stof(val));
					}
				}
				normals.push_back(normal);
			}

		}
		fin.close();
		fin.open(path);
		while (getline(fin, line))
		{
			if (String::startsWith(line, "f"))
			{
				int random = 0;
				vector <int> vertexIndexes;
				vector <int> vertexNormals;
				int count = countNoOfWords(line);

				string stringValues = line;
				
				istringstream iss(stringValues);
				string val;
				
				int n = 0;
				while(iss>>val)
				{
					
					int valSize = val.size();
					if (n != 0)
					{
						const char *letters= new char[valSize+1];
						letters = val.c_str();
						if (letters[1] == '/'&&letters[2] == '/')
						{
							for (int i = 0; i < valSize; i++)
							{
								if (i == 0)
								{
									int num = (int)letters[i] - 48;
									if (count == 5 && n < 4)
										vertexIndexes.push_back(num);
									if (count == 5 && n == 4)
									{
										solid.setFacetVertex(vertices[vertexIndexes[0] - 1]);
										solid.setFacetVertex(vertices[vertexIndexes[2] - 1]);
									}
									solid.setFacetVertex(vertices[num - 1]);
								}
								if (i == 3)
								{
									int num = (int)letters[i] - 48;
									
									if (random == 0 || random % 3 == 0)
									{
									
										solid.setFacetNormal(normals[num - 1]);
									}
									random = random + 1;
								}
							}
						}
						else if (letters[1] == '/'&&letters[2] != '/')
						{
							for (int i = 0; i < valSize; i++)
							{
								if (i == 0)
								{
									int num = (int)letters[i] - 48;
									if (count == 5 && n < 4)
										vertexIndexes.push_back(num);
									if (count == 5 && n == 4)
									{
										solid.setFacetVertex(vertices[vertexIndexes[0] - 1]);
										solid.setFacetVertex(vertices[vertexIndexes[2] - 1]);
									}
									solid.setFacetVertex(vertices[num - 1]);
								}
								if (i == 4)
								{
									int num = (int)letters[i] - 48;
									if (random == 0 || random % 3 == 0)
									{

										solid.setFacetNormal(normals[num - 1]);

									}
									random = random + 1;
								}

							}

						}
					}
					n++;
				}

			}
		}
		fin.close();
	}
	else if (typeOfFile == 3)
	{
		ifstream fin;
		fin.open(path);
		string line;
		vector<Point>vertexData;
		int totalVertices;
		while (getline(fin, line))
		{
			line = String::trim(line);
			if (String::startsWith(line, "OFF"))
			{
				do
				{
					line = iterateLine(fin);
				} while (line.empty() || String::startsWith(line, "#"));

				string stringValues = line;
				istringstream iss(stringValues);
			    string val;
				iss >> val;
				totalVertices = stof(val);
				do
				{
					line = iterateLine(fin);
				} while (line.empty());
				
				for (int i = 0; i < totalVertices; i++)
				{
					Point corner;
					istringstream iff(line);
					for (int j = 0; j < 3; j++)
					{
						string cal;
						iff >> cal;
						if (j == 0)
						{
							corner.setX(stof(cal));
						}
						if (j == 1)
						{
							corner.setY(stof(cal));
						}
						if (j == 2)
						{
							corner.setZ(stof(cal));
						}
					}
					vertexData.push_back(corner);
					line = iterateLine(fin);
				}
			}

			do {
				line = String::trim(line);
				if (String::startsWith(line, "4 "))
				{
					istringstream idd(line);
					vector<int> indexes;
					for (int i = 0; i < 5; i++)
					{
						string word;
						idd >> word;
						if (i != 0)
						{
							indexes.push_back(stof(word));
						}
					}
					solid.setFacetVertex(vertexData[indexes[0]]);
					solid.setFacetVertex(vertexData[indexes[1]]);
					solid.setFacetVertex(vertexData[indexes[2]]);
					solid.setFacetVertex(vertexData[indexes[0]]);
					solid.setFacetVertex(vertexData[indexes[2]]);
					solid.setFacetVertex(vertexData[indexes[3]]);
				}
				if (String::startsWith(line, "3 "))
				{
					istringstream idd(line);
					vector<int> indexes;
					for (int i = 0; i < 4; i++)
					{
						string word;
						idd >> word;
						if (i != 0)
						{
							indexes.push_back(stof(word));
						}
					}
					solid.setFacetVertex(vertexData[indexes[0]]);
					solid.setFacetVertex(vertexData[indexes[1]]);
					solid.setFacetVertex(vertexData[indexes[2]]);
				}
				line = iterateLine(fin);
			} while (!line.empty());
		}

	}
}


void FileReader::readTriangleData(char triangle[50], Point &normal,
	Point &vertex1, Point &vertex2, Point &vertex3)
{
	vector <float>coordinates;
	for (int i = 0; i < 48; i=i+4)
	{
		char n1[4]{ triangle[i],triangle[i+1],triangle[i+2],triangle[i+3] };
		float value = *((float*)n1);
		coordinates.push_back(value);
	}
	normal.setX(coordinates[0]);
	normal.setY(coordinates[1]);
	normal.setZ(coordinates[2]);

	vertex1.setX(coordinates[3]);
	vertex1.setY(coordinates[4]);
	vertex1.setZ(coordinates[5]);

	vertex2.setX(coordinates[6]);
	vertex2.setY(coordinates[7]);
	vertex2.setZ(coordinates[8]);

	vertex3.setX(coordinates[9]);
	vertex3.setY(coordinates[10]);
	vertex3.setZ(coordinates[11]);
}

int FileReader::countNoOfWords(string &line)
{
	int count=0;
	stringstream iss(line);
	string val;
	while (iss >> val)
	{
		count++;
	}
	return count;
}