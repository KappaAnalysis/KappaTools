/* Copyright (c) 2011 - All Rights Reserved
 *   Fred Stober <stober@cern.ch>
 */

#ifndef PTCONFIG_H
#define PTCONFIG_H

#include <boost/python.hpp>
#include "../../Toolbox/interface/IOHelper.h"
#include <map>
#include <vector>
#include <iostream>
#include <string>

class PythonConfig
{
public:
	PythonConfig();
	PythonConfig(const std::string &filename);

	void loadConfig(const std::string &filename);

	template<typename T>
	void put(const std::string &name, const T &obj);
	template<typename T>
	T get(const std::string &name);
	template<typename T>
	T get(const std::string &name, const T &def);

	std::vector<std::string> dir(const std::string &name = "", const bool hide = true);

private:
	boost::python::object main_module, main_namespace, config;

	boost::python::object getattr(const boost::python::object &obj, const std::string &name);
	boost::python::object getattr(const boost::python::object &obj, const std::string &name, const bool abortOnNull);
	void InitPython();

	template<typename T>
	boost::python::object put(const T &obj);
	template<typename T>
	boost::python::object put(const std::vector<T> &obj);
	template<typename Tk, typename Tv>
	boost::python::object put(const std::map<Tk, Tv> &obj);
	template<typename T1, typename T2>
	boost::python::object put(const std::pair<T1, T2> &obj);

	template<typename T>
	bool get(const boost::python::object &obj, T &output);
	template<typename T>
	bool get(const boost::python::object &obj, std::vector<T> &output);
	template<typename Tk, typename Tv>
	bool get(const boost::python::object &obj, std::map<Tk, Tv> &output);
	template<typename T1, typename T2>
	bool get(const boost::python::object &obj, std::pair<T1, T2> &output);
};

#include "Config.hxx"

#endif
