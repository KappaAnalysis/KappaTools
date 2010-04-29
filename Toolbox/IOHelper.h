#ifndef TBIOHELPER_H
#define TBIOHELPER_H

#include <iostream>
#include <iomanip>
#include "VectorTools.h"
#include <set>
#include <map>
#include <boost/io/ios_state.hpp>
#include <boost/property_tree/ptree.hpp>

typedef boost::io::ios_all_saver OStreamGuard;

template<typename T>
void printMatrix(T **matrix, const size_t x, const size_t y, const size_t width = 10);
void printPTree(const boost::property_tree::ptree &pt, const std::string prefix = "");

template<typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const std::map<T1, T2> &m);
template<typename T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &s);
template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v);

#include "IOHelper.hxx"

#endif
