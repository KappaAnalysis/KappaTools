#ifndef TBSTRINGTOOLS_H
#define TBSTRINGTOOLS_H

#include <cstdlib>
#include <iostream>
#include <sstream>

// This construct is needed to stringify -D defines:
#define QUOTE(x) XQUOTE(x)
#define XQUOTE(x) #x

template <typename T>
static T parse(const std::string &s, bool fail = true);

template <typename T>
static std::string str(const T &i);

std::string tolower(std::string s);
std::string toupper(std::string s);

#include "StringTools.hxx"

#endif
