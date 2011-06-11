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

vector<string> split(const string &str, const string &delim, const size_t maxSize)
{
	vector<string> tokens;

	size_t p0 = 0, p1 = string::npos;
	while ((p0 != string::npos) && ((maxSize == 0) || (tokens.size() < maxSize)))
	{
		p1 = str.find_first_of(delim, p0);
		if (p1 != p0)
		{
			string token = str.substr(p0, p1 - p0);
			tokens.push_back(token);
		}
		p0 = str.find_first_not_of(delim, p1);
	}
	if (p0 != string::npos)
		tokens.push_back(str.substr(p0));
	return tokens;
}

vector<string> tokenize(const string &str, const string &delim, const bool escape)
{
	if (!escape)
		return split(str, delim);
	vector<string> result;
	vector<string> esc = split(str, "'");
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
			vector<string> tok = split(esc[i], delim);
			copy(tok.begin(), tok.end(), back_inserter(result));
		}
	return result;
}

template <>
std::string str<bool>(const bool &i)
{
	if (i)
		return "true";
	return "false";
}

template <>
std::string parse<std::string>(const std::string &s, bool)
{
	return s;
}

template <>
bool parse<bool>(const std::string &s, bool)
{
	static const std::string s_true[] = {"true", "yes", "y", "1"};
	static const std::string s_false[] = {"false", "no", "n", "0"};

	const std::string tmp = tolower(s);
	for (size_t i = 0; i < sizeof(s_true) / sizeof(std::string); ++i)
		if (s_true[i] == tmp)
			return true;
	for (size_t i = 0; i < sizeof(s_false) / sizeof(std::string); ++i)
		if (s_false[i] == tmp)
			return false;
	std::cerr << "Parse error - invalid bool: " << s;
	return false;
}
