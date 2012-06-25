#include "StringTools.h"
#include <algorithm>
#include <cstdlib>
#include <stdarg.h>
#include <stdio.h>

void reportParseError(const std::string &s)
{
	std::cerr << "Parse error: " << s;
	exit(0);
}

std::string tolower(std::string s)
{
	transform(s.begin(), s.end(), s.begin(), (int(*)(int))tolower);
	return s;
}

std::string toupper(std::string s)
{
	transform(s.begin(), s.end(), s.begin(), (int(*)(int))toupper);
	return s;
}

std::vector<std::string> split(const std::string &str, const std::string &delim, const size_t maxSize)
{
	std::vector<std::string> tokens;

	size_t p0 = 0, p1 = std::string::npos;
	while ((p0 != std::string::npos) && ((maxSize == 0) || (tokens.size() < maxSize)))
	{
		p1 = str.find_first_of(delim, p0);
		if (p1 != p0)
		{
			std::string token = str.substr(p0, p1 - p0);
			tokens.push_back(token);
		}
		p0 = str.find_first_not_of(delim, p1);
	}
	if (p0 != std::string::npos)
		tokens.push_back(str.substr(p0));
	return tokens;
}

std::vector<std::string> tokenize(const std::string &str, const std::string &delim, const bool escape)
{
	if (!escape)
		return split(str, delim);
	std::vector<std::string> result;
	std::vector<std::string> esc = split(str, "'");
	for (unsigned int i = 0; i < esc.size(); i++)
		if (i % 2 == 1)
		{
			if (delim.find_first_of(*(esc[i - 1].rbegin())) == std::string::npos)
				result.back() += esc[i];
			else
				result.push_back(esc[i]);
		}
		else
		{
			std::vector<std::string> tok = split(esc[i], delim);
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
bool parse<bool>(const std::string &s, bool fail)
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
	if (fail)
		reportParseError(s);
	return false;
}

std::string lstrip(const std::string &input, const std::string rm)
{
	size_t pos = 0;
	if (input.size() == 0)
		return input;
	while ((pos < input.size()) && in(input[pos], rm))
		pos++;
	return input.substr(pos);
}

std::string rstrip(const std::string &input, const std::string rm)
{
	size_t pos = input.size();
	if (pos == 0)
		return input;
	while (in(input[--pos], rm) && (pos > 0));
	return input.substr(0, pos + 1);
}

std::string strip(const std::string &input, const std::string rm)
{
	return rstrip(lstrip(input, rm), rm);
}

template<>
bool in(const char x, const std::string y)
{
	return y.find_first_of(x) != std::string::npos;
}

template<>
bool in(const char x, const std::string &y)
{
	return y.find_first_of(x) != std::string::npos;
}

template<>
bool in(const std::string x, const std::vector<std::string> &y)
{
	return std::find(y.begin(), y.end(), x) != y.end();
}

template<>
bool in(const std::string &x, const std::vector<std::string> &y)
{
	return std::find(y.begin(), y.end(), x) != y.end();
}

bool startswith(const std::string &input, const std::string search)
{
	return input.find(search) == 0;
}

bool endswith(const std::string &input, const std::string search)
{
	return input.find(search) == input.size() - search.size();
}

std::string basename(const std::string &input)
{
	std::vector<std::string> tmp = split(input, "/");
	if (tmp.size() == 0)
		return "";
	return tmp[tmp.size() - 1];
}

std::string dirname(const std::string &input)
{
	std::vector<std::string> tmp = split(input, "/");
	if (tmp.size() == 0)
		return "";
	tmp.pop_back();
	if (input[0] == '/')
		return "/" + join("/", tmp);
	return join("/", tmp);
}

// sort variable names in descending order
static const bool cmp(const std::pair<std::string, std::string> &a, const std::pair<std::string, std::string> &b)
{
	return a.first.length() > b.first.length();
}

std::string substVars(std::string in, std::vector<std::pair<std::string, std::string> > vars)
{
	// Sort temp varlist (long names to the front)
	sort(vars.begin(), vars.end(), cmp);
	// Variable substitution
	for (size_t i = 0; i < vars.size(); i++)
	{
		in = replaceall(in, "${" + vars[i].first + "}", vars[i].second);
		in = replaceall(in, "$" + vars[i].first, vars[i].second);
	}
	return in;
}

std::string replace(const std::string &input, const std::string &find, const std::string &replace)
{
	int pos = input.find(find);
	if (pos < 0)
		return input;
	std::string temp = input;
	temp.replace(pos, find.size(), replace);
	return temp;
}

std::string replaceall(const std::string &input, const std::string &find, const std::string &replace)
{
	int pos = 0;
	std::string temp = input;
	while ((pos = temp.find(find, pos)) >= 0)
	{
		temp.replace(pos, find.size(), replace);
		pos = pos - find.size() + replace.size() + 1;
	}
	return temp;
}

stlprintf::stlprintf(const char *format, ...)
{
	va_list args;
	va_start (args, format);
	char *tmp = 0;
	if (vasprintf (&tmp, format, args) < 0)
		tmp = 0;
	va_end (args);
	if (tmp)
		str = tmp;
}

stlprintf::operator const char*() const
{
	return str.c_str();
}

stlprintf::operator const std::string() const
{
	return str;
}
