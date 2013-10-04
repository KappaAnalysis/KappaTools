/* Copyright (c) 2010 - All Rights Reserved
 *   Fred Stober <stober@cern.ch>
 *   Manuel Zeise <zeise@cern.ch>
 */

#ifndef TBCMDLINESETUP_H
#define TBCMDLINESETUP_H

#include <string>
#include <map>
#include "StringTools.h"

// Command line option uses either no argument / requires it / is optional
enum CmdLineOptionArg { CL_None = 0, CL_Req = 1, CL_Opt = 2 };
enum CmdLinePresets { OPT_None = 0, OPT_Help = 1, OPT_Show = 2 };

// Base class for command line options
struct CmdLineOption
{
	CmdLineOption(const char s, const std::string l, const std::string h = "",
		const CmdLineOptionArg a = CL_None);
	virtual ~CmdLineOption() {}

	std::string shortName;
	std::string longName;
	std::string help;
	CmdLineOptionArg argument;

	virtual void FoundOption(std::string arg = "") {}
	virtual std::string PrintOption() const { return ""; }
	virtual std::string PrintHelp() const { return help; }
};

// Print current value of option
std::ostream &operator<<(std::ostream &os, const CmdLineOption &opt);

// Base template class for cmd options with value
template<typename T>
struct CmdLineOptionValue : public CmdLineOption
{
	CmdLineOptionValue(const char s, const std::string l, const std::string h = "",
		const T &def = T(), const CmdLineOptionArg a = CL_Req)
		: CmdLineOption(s, l, h, a), value(def) {}

	operator const T() const { return value; }
	const T &Value() const { return value; }

	virtual void FoundOption(std::string arg = "") { value = parse<T>(arg); }
	virtual std::string PrintOption() const { return str(value); }
private:
	T value;
};

// Special template class for cmd options with string value
template<>
struct CmdLineOptionValue<std::string> : public CmdLineOption
{
	CmdLineOptionValue(const char s, const std::string l, const std::string h = "",
		const std::string &def = std::string(), const CmdLineOptionArg a = CL_Req)
		: CmdLineOption(s, l, h, a), value(def) {}

	operator const char*() const { return value.c_str(); }
	operator const std::string() const { return value; }
	const std::string &Value() const { return value; }

	virtual void FoundOption(std::string arg = "") { value = parse<std::string>(arg); }
	virtual std::string PrintOption() const { return str(value); }
private:
	std::string value;
};

// Base template class for cmd options with vector of values
template<typename T>
struct CmdLineOptionVector : public CmdLineOption
{
	CmdLineOptionVector(const char s, const std::string l, const std::string h = "",
		const std::string &def = "", const CmdLineOptionArg a = CL_Req)
		: CmdLineOption(s, l, h, a) { FoundOption(def); }

	const T &operator[](const size_t idx) { return value[idx]; }
	operator const std::vector<T>() const { return value; }
	const std::vector<T> &Value() const { return value; }
	const size_t size() const { return value.size(); }

	virtual void FoundOption(std::string arg = "")
	{
		value.clear();
		if (arg == "")
			return;
		std::vector<std::string> tmp = split(arg, ",");
		for (size_t i = 0; i < tmp.size(); ++i)
			value.push_back(parse<T>(tmp[i]));
	}
	virtual std::string PrintOption() const
	{
		std::string tmp;
		if (value.size() > 0)
		{
			for (size_t i = 0; i < value.size() - 1; ++i)
				tmp += str(value[i]) + ", ";
			tmp += str(value[value.size() - 1]);
		}
		return tmp;
	}
private:
	std::vector<T> value;
};

// Base template class for cmd options toggle
template<typename T>
struct CmdLineOptionSwitch : public CmdLineOption
{
	CmdLineOptionSwitch(const char s, const std::string l, const std::string h = "",
		const T &def = T(), const CmdLineOptionArg a = CL_None)
		: CmdLineOption(s, l, h, a), value(def) {}

	operator const T() const { return value; }
	const T &Value() const { return value; }

	virtual void FoundOption(std::string arg = "") { value = !value; }
	virtual std::string PrintOption() const { return str(value); }
private:
	T value;
};

// Base template class for cmd options toggle
struct CmdLineOptionCallback : public CmdLineOption
{
	CmdLineOptionCallback(const char s, const std::string l, const std::string h = "",
		void (*c)(std::string) = 0, const CmdLineOptionArg a = CL_None)
		: CmdLineOption(s, l, h, a), pf(c) {}

	virtual void FoundOption(std::string arg = "") { if (pf) pf(arg); }
private:
	void (*pf)(std::string);
};

struct CmdLineInfo
{
	int id;
	std::string arg;
};

struct CmdLineBase
{
	static void RegisterOption(CmdLineOption *opt);
	static bool GetInfo(const int argc, char **argv, CmdLineInfo *info);
	static void DefaultAction(CmdLineInfo *info);

	static void Show(std::string arg = "");
	static void PrintHelp(std::string arg = "");
	static void PrintVersion(std::string arg = "");

	static std::string basename;
	static std::vector<std::string> ParseArgs(const int argc, char **argv, int presets = OPT_None);
private:
	static bool displayParams;
	static bool displayHelp;
	static size_t pWidth;
	static std::vector<CmdLineOption*> options;

	static void SetParamShow(std::string arg = "");
	static void SetPrintHelp(std::string arg = "");
};

#endif
