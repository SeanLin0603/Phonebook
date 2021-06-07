#include "pch.h"
#include "Utilities.h"

using namespace std;

bool IsNumber(string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (!isdigit(str[i]))
		{
			return false;
		}
	}
	return true;
}

string convert2Uppercase(string str)
{
	string output;
	for (int i = 0; i < str.size(); i++)
	{
		output.push_back(toupper(str[i]));
	}
	return output;
}