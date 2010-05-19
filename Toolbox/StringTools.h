#ifndef TBSTRINGTOOLS_H
#define TBSTRINGTOOLS_H

#include <vector>
#include <cstdlib>
#include <iostream>
#include <sstream>

// This construct is needed to stringify -D defines:
#define QUOTE(x) XQUOTE(x)
#define XQUOTE(x) #x

template <typename T>
T parse(const std::string &s, bool fail = true);
template <>
std::string parse<std::string>(const std::string &s, bool);
template <>
bool parse<bool>(const std::string &s, bool);

template <typename T>
std::string str(const T &i);
template <>
std::string str<bool>(const bool &i);

std::string tolower(std::string s);
std::string toupper(std::string s);

std::vector<std::string> tokenize(const std::string &str, const std::string &delim = " ", const bool escape = false);

#include "StringTools.hxx"

#endif
