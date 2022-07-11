#pragma once
#include <string>

using namespace std;

class String
{
public :
	 static string WHITESPACE;
	 static string lTrim(const string& line);
	 static string rTrim(const string& line);
	 static string trim(const string& line);
	 static bool startsWith(const string &,const string &toMatch); // to check if the substring is starting string of complete string
};

