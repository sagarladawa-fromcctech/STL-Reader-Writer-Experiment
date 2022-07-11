#include <fstream>
#include <iostream>
#include "FileType.h"
#include "String.h"

using namespace std;

string FileType::iterateLine(ifstream&fin )
{
	string line;
	getline(fin, line);
	return line;
}
void FileType::checkValidOrNot(string &path)
{
	ifstream fin;
	fin.open(path);
	if (fin.fail())
	{
	 cout <<endl<< "\tThe file path entered is Invalid,please Enter a valid file name" << endl;
	 cout << "\tNew path : \t";
	 getline(cin, path);
	 checkValidOrNot(path);
	}
}
int FileType::checkTypeOfFile(string &path)
{
	ifstream fin;
	fin.open(path);
	if (fin.fail())
	{
		return -1;
	}
	string line;
	line = iterateLine(fin);
	line = String::trim(line);  // trim the blank spaces from left and right side of the line
	int x = (int)path.size();
	string file = path.substr(x-3,x);

		if (String::startsWith(line, "solid")) //check if the line starts with "facet normal"
		{
			do
			{
				line = iterateLine(fin);
			} while (line.empty() || String::startsWith(line,"#"));
			
			line = String::trim(line);
			if (String::startsWith(line, "facet"))
			{
				return 0;
			}
		}
		
		else if (String::startsWith(file,"obj"))
		{
			return 2;
		}
		else if (String::startsWith(file, "off"))
		{
			return 3;
		}
		else
		{
			return 1;
		}
		
	fin.close();
}