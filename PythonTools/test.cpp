#include "Config.h"
#include "../Toolbox/IOHelper.h"

struct TestState
{
	std::string name;
	std::map<std::string, std::string> dict;
	std::vector<double> list;
};

std::ostream &operator<<(std::ostream &os, const TestState &ts)
{
	return os
		<< "\tname: " << ts.name
		<< "\tdict: " << ts.dict
		<< "\tlist: " << ts.list;
}

template<>
bool PythonConfig::get(const boost::python::object &obj, TestState &output)
{
	boost::python::tuple tmp(obj);
	if (!get(tmp[0], output.name))
		return false;
	if (!get(tmp[1], output.dict))
		return false;
	if (!get(tmp[2], output.list))
		return false;
	return true;
}

int main()
{
	PythonConfig pc;
	pc.put<std::string>("in1", "putted string");
	pc.put<int>("in2", 123);
	pc.put<double>("in3", 3.14159);
	pc.loadConfig("test.py");

	std::cout << pc.get<std::string>("string") << std::endl;
	std::cout << pc.get<std::string>("string1", "default") << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << pc.get<std::vector<int> >("test") << std::endl;
	std::cout << pc.get<std::map<int, int> >("dicttest") << std::endl;
	std::cout << pc.get<std::map<std::string, int> >("dicttest1") << std::endl;
	std::cout << pc.get<std::string>("xyz.a") << std::endl;
	std::cout << pc.get<TestState>("obj") << std::endl;
	std::cout << pc.get<std::pair<double, std::string> >("pair") << std::endl;
	std::cout << pc.get<std::vector<std::pair<double, double> > >("pairlist") << std::endl;

	std::cout << pc.dir() << std::endl;
	std::cout << pc.dir("xyz") << std::endl;

	std::cout << pc.get<std::string>("error") << std::endl;

	return 0;
}
