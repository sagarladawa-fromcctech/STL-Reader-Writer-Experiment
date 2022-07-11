#pragma once
#include <iostream>
#include "String.h"


string String::WHITESPACE = "\n\r\t\f\v ";


string String::lTrim(const string& line)
{
	size_t start = line.find_first_not_of(WHITESPACE); // find the position of letter in string that is not among the whitespaces
	return (start == string::npos) ? "" : line.substr(start);  // return the substring free from left whitespaces
}

 string String::rTrim(const string& line)
{
	size_t end = line.find_last_not_of(WHITESPACE); //find the position of letter in string that is not among the whitespaces
	return (end == string::npos) ? "" : line.substr(0, end + 1); // return the substring free from right whitespaces
}

string String::trim(const string& line)
{
	return rTrim(lTrim(line));
}
bool String::startsWith(const string & mainStr,const string &toMatch) // to check if the substring is starting string of complete string
{
	
	if (mainStr.find(toMatch) == 0)
		return true;
	else
		return false;
}