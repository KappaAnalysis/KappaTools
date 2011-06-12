#ifndef TBVECTORTOOLS_H
#define TBVECTORTOOLS_H

#include <string>
#include <iostream>
#include <iterator>
#include <vector>
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

#include "VectorTools.hxx"

#endif
