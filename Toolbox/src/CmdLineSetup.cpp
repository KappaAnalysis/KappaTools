/* Copyright (c) 2010 - All Rights Reserved
 *   Fred Stober <stober@cern.ch>
 */

#include "CmdLineSetup.h"
#include <getopt.h>
#include <string.h>
#include <iomanip>
#include <cstdlib>

using namespace std;

size_t CmdLineBase::pWidth = 0;
string CmdLineBase::basename = "";
vector<CmdLineOption*> CmdLineBase::options;
bool CmdLineBase::displayParams = false;
bool CmdLineBase::displayHelp = false;

CmdLineOption::CmdLineOption(const char s, const string l,
	const string h, const CmdLineOptionArg a)
	: longName(l), help(h), argument(a)
{
	if (s == 0)
		shortName = "";
	else
		shortName = s;
	CmdLineBase::RegisterOption(this);
}

ostream &operator<<(ostream &os, const CmdLineOption &opt)
{
	// Display name of option
	if (opt.shortName != "")
		os << "\t-" << opt.shortName << ",";
	else
		os << "\t   ";
	if (opt.longName != "")
		os << " --" << opt.longName;
	return os;
}

void CmdLineBase::RegisterOption(CmdLineOption *opt)
{
	for (size_t i = 0; i < options.size(); ++i)
	{
		string msg = "";
		if ((opt->shortName == options[i]->shortName) && (opt->shortName != ""))
			msg = "Short name for command line options are not unique!";
		if ((opt->longName == options[i]->longName) && (opt->longName != ""))
			msg = "Long name for command line options are not unique!";
		if (!msg.empty())
		{
			cout << msg << endl << *opt << endl << *(options[i]) << endl;
			exit(1);
		}
	}
	pWidth = max(pWidth, opt->longName.size());
	options.push_back(opt);
}

struct option InitOpt(const string &name, const CmdLineOptionArg args, const int val)
{
	struct option result;
	result.name = name.c_str();
	result.has_arg = args;
	result.flag = 0;
	result.val = val;
	return result;
}

bool CmdLineBase::GetInfo(const int argc, char **argv, CmdLineInfo *info)
{
	vector<struct option> optsarray;
	for (size_t i = 0; i < options.size(); ++i)
	{
		if (options[i]->longName != "")
			optsarray.push_back(InitOpt(options[i]->longName, options[i]->argument, i));
		if (options[i]->shortName != "")
			optsarray.push_back(InitOpt(options[i]->shortName, options[i]->argument, i));
	}
	optsarray.push_back(option());
	memset(&(optsarray[optsarray.size() - 1]), 0, sizeof(struct option));
	info->id = getopt_long_only(argc, argv, "", &(optsarray[0]), 0);
	if ((info->id < 0) || (info->id > (int)options.size()))
		return false;
	if (optarg != 0)
		info->arg = string(optarg);
	return true;
}

void CmdLineBase::DefaultAction(CmdLineInfo *info)
{
	CmdLineOption* optObj = options[info->id];
	if (optObj->argument != CL_None)
		optObj->FoundOption(string(info->arg));
	else
		optObj->FoundOption();
}

void CmdLineBase::Show(string arg)
{
	displayParams = true;
	stringstream ss;
	ss << "Used parameters: " << endl;
	for (size_t i = 0; i < options.size(); ++i)
	{
		if (options[i]->PrintOption() == "")
			continue;
		ss << "\t" << setw(pWidth) << options[i]->longName
			<< " = " << options[i]->PrintOption() << endl;
	}
	if (arg != "")
		ss << "Additional parameters:" << endl << "\t" << arg << endl;
	cout << ss.str() << endl;
}

void CmdLineBase::PrintHelp(string arg)
{
	cout << "Available command line options for " << basename << ":" << endl;
	for (size_t i = 0; i < options.size(); ++i)
	{
		cout << *(options[i]);
		for (size_t f = options[i]->longName.size(); f < pWidth; ++f)
			cout << " ";
		cout << " : " << options[i]->PrintHelp() << endl;
	}
	exit(1);
}

vector<string> CmdLineBase::ParseArgs(const int argc, char **argv, int presets)
{
	basename = string(argv[0]);
	if (presets & OPT_Help)
	{
		static CmdLineOptionCallback clHelp('h', "help",
			"Print help", CmdLineBase::SetPrintHelp);
	}
	if (presets & OPT_Show)
	{
		static CmdLineOptionCallback clParams('P', "parameters",
			"Print parameters", CmdLineBase::SetParamShow);
	}

	CmdLineInfo opt;
	while (GetInfo(argc, argv, &opt))
		DefaultAction(&opt);
	// Collect the other arguments
	vector<string> leftover;
	for (int i = optind; i < argc; i++)
		leftover.push_back(argv[i]);
	if (displayParams)
		Show(KappaTools::join(", ", leftover));
	if (displayHelp)
		PrintHelp();
	return leftover;
}

void CmdLineBase::SetParamShow(string arg)
{
	displayParams = true;
}

void CmdLineBase::SetPrintHelp(string arg)
{
	displayHelp = true;
}
