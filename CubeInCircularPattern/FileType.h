#pragma once

#include <string>
using namespace std;

class FileType
{
 private:
	 static string iterateLine(ifstream &fin);
 public :
	static int checkTypeOfFile(string &path);
	static void checkValidOrNot(string &path);
};