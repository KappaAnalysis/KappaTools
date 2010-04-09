#include "StringTools.h"
#include <algorithm>
#include <stdlib.h>

using namespace std;

string tolower(string s)
{
	transform(s.begin(), s.end(), s.begin(), (int(*)(int))tolower);
	return s;
}

string toupper(string s)
{
	transform(s.begin(), s.end(), s.begin(), (int(*)(int))toupper);
	return s;
}
