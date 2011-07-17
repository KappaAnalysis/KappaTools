#ifndef TBVECTORTOOLS_H
#define TBVECTORTOOLS_H

#include <string>
#include <iostream>
#include <iterator>
#include <vector>
#include <boost/algorithm/string/regex.hpp>
#include "StringTools.h"

std::vector<int> seq(int last);
std::vector<int> seq(int start, int last);
template<typename T>
std::vector<T> seq(T start, T inc, T last);

template<typename Tlambda, typename Tin>
std::vector<std::string> strmap(const Tlambda &lambda, const Tin &list);

template<typename Tin>
std::vector<std::string> fmtmap(const std::string &str, const Tin &list, const std::string &param = "$1");

template<typename Tlambda, typename Tin>
Tin mymap(const Tlambda &lambda, const Tin &list);

template<typename Tin>
std::string join(const std::string delim, const Tin &cont);

template<typename Tin, typename Tp1>
std::vector<Tp1> getFirst(const Tin &in);
template<typename Tin, typename Tp1>
std::vector<Tp1> getSecond(const Tin &in);

template<typename Tin, typename Tout>
Tout convert(const Tin &in);

template<typename Tk, typename Tv>
std::vector<Tv> match(const std::string &pattern, const std::map<Tk, Tv> &in,
	const boost::regex::flag_type flags = boost::regex::extended);
template<typename Tk, typename Tv>
std::vector<Tk> match_keys(const std::string &pattern, const std::map<Tk, Tv> &in,
	const boost::regex::flag_type flags = boost::regex::extended);
std::vector<std::string> match(const std::string &pattern, const std::vector<std::string> &in,
	const boost::regex::flag_type flags = boost::regex::extended);

#include "VectorTools.hxx"

#endif
