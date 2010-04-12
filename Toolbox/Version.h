#ifndef TBVERSION_H
#define TBVERSION_H

#include <string>
#include <iostream>
#include <map>

struct VersionInfo
{
	VersionInfo(std::string subsystem, std::string version);
	static void print(std::ostream &os);
	static std::map<std::string, std::string> versions;
};

#endif
