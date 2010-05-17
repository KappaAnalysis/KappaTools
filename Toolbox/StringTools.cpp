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

vector<string> tokenize1(const string &str, const string &delim)
{
	vector<string> tokens;

	size_t p0 = 0, p1 = string::npos;
	while (p0 != string::npos)
	{
		p1 = str.find_first_of(delim, p0);
		if (p1 != p0)
		{
			string token = str.substr(p0, p1 - p0);
			tokens.push_back(token);
		}
		p0 = str.find_first_not_of(delim, p1);
	}
	return tokens;
}

vector<string> tokenize(const string &str, const string &delim, const bool escape)
{
	if (!escape)
		return tokenize1(str, delim);
	vector<string> result;
	vector<string> esc = tokenize1(str, "'");
	for (unsigned int i = 0; i < esc.size(); i++)
		if (i % 2 == 1)
		{
			if (delim.find_first_of(*(esc[i - 1].rbegin())) == string::npos)
				result.back() += esc[i];
			else
				result.push_back(esc[i]);
		}
		else
		{
			vector<string> tok = tokenize1(esc[i], delim);
			copy(tok.begin(), tok.end(), back_inserter(result));
		}
	return result;
}
