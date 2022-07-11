#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <algorithm>
#include <vector>
#include <sstream>
#include <Windows.h>
#include "Point.h"
#include "Solid.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "String.h"
#include "Transformation.h"
#include "Vector.h"
#include "FileType.h"

int main()
{
	FileReader InputCadFile;
	cout << "Enter the complete path of the file(stl,off,obj)" << endl << endl;
	string path;
	getline(cin, path);
	FileType::checkValidOrNot(path);
	int typeOfFile = FileType::checkTypeOfFile(path);
	cout << "*****************************************************************************************" << endl;
		switch (typeOfFile)
		{
		case 0:
		{cout << "\t\tInput file is of STL format and ASCII encoded" << endl << endl;
		}
		case 1:
		{cout << "\t\tInput file is of STL format and binary encoded" << endl << endl;
		}
		case 2: {
			cout << "\t\tInput file is of OBJ file format and ASCII encoded" << endl << endl;
			break;
		}
		case 3:
		{
			cout << "\t\tInput file is of OFF file format and ASCII encoded" << endl << endl;
			break;
		}
		}

		int position = (int)path.rfind('/');

		string location = path.substr(0, position + 1);

		int noOfFacets = 0;
		int noOfVertices = 0;
		int noOfEdges = 0;
		Solid solidOne;

		InputCadFile.calculateNoOfVerticesAndFacets(path, noOfFacets, 
			                    noOfVertices, typeOfFile,noOfEdges); //To calculate noof facets and vertices

		cout << endl << "\t\tThe number of total triangles formed in this file are " << noOfFacets << endl << endl;

		InputCadFile.StoreFileDataInObject(path,solidOne, typeOfFile);
		
		
			vector <int> allAngles;
			int noOfDivision;
			int baseAngle = 0;
			cout << endl << endl << "How many such solids you want to see in circular pattern  ? : "
				<< "   ";
			cin >> noOfDivision;
			cout << endl;
			int angleIncrement;
			if (noOfDivision != 0)
			{
				 angleIncrement = 360 / noOfDivision;
			}
			for (int i = 0; i < noOfDivision; i++)
			{
				allAngles.push_back(baseAngle);
				baseAngle = baseAngle + angleIncrement;
			}

			float radiusOfCircle;
			cout << endl << "enter radius of circle on whoose circumference the solids are to be placed: " << "\t";
			cin >> radiusOfCircle;

			int choiceOfAxis;
			cout <<endl<<endl<< "\t\tChoose along which axis the solid to be rotated " << endl;
			cout << endl << "\t\tEnter 1 for around x-axis :\t";
			cout << endl << "\t\tEnter 2 for around y-axis :\t";
			cout << endl << "\t\tEnter 3 for around z-axis :\t ";
			cout << endl << "\t\tEnter 4 for around a user defined axis :\t";
			cout << endl << "\tchoice :  ";
			cin >> choiceOfAxis;
			
			vector <Vector> allDirectionVectors;
			
			Vector userVector;
			Vector normalToUserVector;

			vector <float> line;
			vector <float> normalLine;

			if (choiceOfAxis == 1)
			{
				line.push_back(1);
				line.push_back(0);
				line.push_back(0);

				normalLine.push_back(0);
				normalLine.push_back(1);
				normalLine.push_back(0);

				for (int i = 0; i < 3; i++)
				{
					userVector.setVectorCoefficients(line[i]);
					normalToUserVector.setVectorCoefficients(normalLine[i]);
				}
			}
			if (choiceOfAxis == 2)
			{
				line.push_back(0);
				line.push_back(1);
				line.push_back(0);

				normalLine.push_back(1);
				normalLine.push_back(0);
				normalLine.push_back(0);

				for (int i = 0; i < 3; i++)
				{
					userVector.setVectorCoefficients(line[i]);
					normalToUserVector.setVectorCoefficients(normalLine[i]);
				}
			}
			if (choiceOfAxis == 3)
			{
				
				line.push_back(0);
				line.push_back(0);
				line.push_back(1);

				normalLine.push_back(0);
				normalLine.push_back(1);
				normalLine.push_back(0);

				for (int i = 0; i < 3; i++)
				{
					userVector.setVectorCoefficients(line[i]);
					normalToUserVector.setVectorCoefficients(normalLine[i]);
				}

			}
			if (choiceOfAxis == 4)
			{
				float coordinate;
				cout << "\t\tEnter the coordinates for the vector" << endl;
				cout << "\t\tEnter i coordinate:\t";
				cin >> coordinate;
				line.push_back(coordinate);
				cout << "\t\tEnter j coordinate:\t";
				cin >> coordinate;
				line.push_back(coordinate);
				cout << "\t\tEnter k coordinate:\t";
				cin >> coordinate;
				line.push_back(coordinate);
				if (line[0] == 0 && line[1] == 1 && line[2]==0)
				{
					normalLine.push_back(1);
					normalLine.push_back(0);
					normalLine.push_back(0);
					for (int i = 0; i < 3; i++)
					{
						userVector.setVectorCoefficients(line[i]);
						normalToUserVector.setVectorCoefficients(normalLine[i]);
					}
				}
				else if (line[0] == 1 && line[1] == 0 && line[2]==0)
				{
					normalLine.push_back(0);
					normalLine.push_back(1);
					normalLine.push_back(0);
					for (int i = 0; i < 3; i++)
					{
						userVector.setVectorCoefficients(line[i]);
						normalToUserVector.setVectorCoefficients(normalLine[i]);
					}
				}
				else if (line[0] == 0 && line[1] == 0 && line[2] == 1)
				{
					normalLine.push_back(1);
					normalLine.push_back(0);
					normalLine.push_back(0);
					for (int i = 0; i < 3; i++)
					{
						userVector.setVectorCoefficients(line[i]);
						normalToUserVector.setVectorCoefficients(normalLine[i]);
					}
				}
				else if(line[2] != 0)
				{
					normalLine.push_back(1);
					normalLine.push_back(1);
					normalLine.push_back((-1 * (line[0] + line[1])) / line[2]);
					for (int i = 0; i < 3; i++)
					{
						userVector.setVectorCoefficients(line[i]);
						normalToUserVector.setVectorCoefficients(normalLine[i]);
					}
				}
				else if(line[1]!=0)
				{
					normalLine.push_back(1);
					normalLine.push_back((-1 * (line[0] + line[2])) / line[1]);
					normalLine.push_back(1);
					for (int i = 0; i < 3; i++)
					{
						userVector.setVectorCoefficients(line[i]);
						normalToUserVector.setVectorCoefficients(normalLine[i]);
					}
				}
				else
				{
					normalLine.push_back(0);
					normalLine.push_back(1);
					normalLine.push_back(0);
					for (int i = 0; i < 3; i++)
					{
						userVector.setVectorCoefficients(line[i]);
						normalToUserVector.setVectorCoefficients(normalLine[i]);
					}
				}
			}

			Vector firstNormal = normalToUserVector;
			normalToUserVector.findUnitVector();
			allDirectionVectors.push_back(normalToUserVector);

			for (int i = 1; i < noOfDivision; i++)
			{
				Vector instanceVector;
				instanceVector.rotatevector(userVector, firstNormal, allAngles[i]);
				instanceVector.findUnitVector();
				allDirectionVectors.push_back(instanceVector);
			}
			
			vector <Solid> allSolids;

			for (int i = 0; i < noOfDivision; i++)
			{
				Solid instanceSolid;
				instanceSolid = Transformation::translateSolidVertexAlongVector(solidOne, allDirectionVectors[i]
					, noOfVertices, noOfFacets, radiusOfCircle);
				allSolids.push_back(instanceSolid);
			}

			if (typeOfFile != 3)
			{
				cout << endl << endl << "\t\tChoose to write among the following file formats" << endl << endl;
				cout << "\t\tEnter 0 for writing in Ascii stl file fomat " << endl;
				cout << "\t\tEnter 1 for writing in binary stl file format" << endl;
				cout << "\t\tEnter 2 for writing in Obj File file format " << endl;
				cout << "\t\tEnter 3 for writing in OFF file format" << endl;
				int choiceOfOutputFile;
				cout << "\tchoice : ";
				cin >> choiceOfOutputFile;
				typeOfFile = choiceOfOutputFile;
			}
			
			FileWriter fWrite;

			fWrite.writestlfile(solidOne, noOfFacets, location, 
				                typeOfFile, noOfEdges, noOfDivision);
			
			for (int i = 0; i < noOfDivision; i++)
			{
				fWrite.writestlfile(allSolids[i], noOfFacets, location,
					typeOfFile,noOfEdges, noOfDivision);
			}

			cout <<endl<< "The newly created STL file is generated at same location i.e " << location << endl;
			char cho;
			cout << endl<<"\t\tDo you want to see the file in app" << endl;
			cout << "\t\tEnter y- for yes" << endl;
			cout << "\t\tEnter n- for no" <<endl;
			cout << "\tchoice : ";
			cin >> cho;
			if (typeOfFile == 0)
			{
				location = location + "solid.stl";
			}
			if (typeOfFile == 1)
			{
				location = location + "solid.stl";
			}
			if (typeOfFile == 2)
			{
				location = location + "solid.obj";
			}
			if (typeOfFile == 3)
			{
				location = location + "solid.off";
			}

			string pathName;

			if (typeOfFile == 0 || typeOfFile == 1 || typeOfFile == 2)
			{
				pathName = "paraview.exe \"" + location + "\"";
			}
			else
			{
				pathName = "meshlab.exe \"" + location + "\"";
			}

			if (cho == 'y')
			{
				system(pathName.c_str());

			}

			char lo;
			cin >> lo;
		
}
