/* Copyright (c) 2012 - All Rights Reserved
 *   Fred Stober <stober@cern.ch>
 */

#define DEBUG
#include "../interface/libKToolbox.h"
#include <iostream>
#include <iterator>

using namespace std;

double myadd(const double &x) { return x + 12.5; }
std::string myconv(const double &x) { return "XXX" + KappaTools::str(x); }

// Not an ideal example on how to use CmdLineBase...
struct CmdLineSetup
{
	CmdLineSetup(const int argc, char **argv) :
		optStr('s', "string", "String", "string default"),
		optInt('i', "integer", "Integer", 3),
		optDouble('d', "double", "Double", 2.3),
		optStrV('v', "svector", "Vector<string>", "a,b,c"),
		optDV('D', "dvector", "Vector<double>", "3.2,1.54,12.2"),
		optBool('b', "bool", "Bool", true)
	{
		CmdLineBase::ParseArgs(argc, argv, OPT_Help | OPT_Show);
		CmdLineBase::Show();
	}
	CmdLineOptionValue<std::string> optStr;
	CmdLineOptionValue<int> optInt;
	CmdLineOptionValue<double> optDouble;
	CmdLineOptionVector<std::string> optStrV;
	CmdLineOptionVector<double> optDV;
	CmdLineOptionSwitch<bool> optBool;
};

int main(int argc, char **argv)
{
	CmdLineOptionVector<int> otherOption('I', "ivector", "Vector<int>", "1,2,3,5,8");
	CmdLineSetup(argc, argv);

	// Debug.h //////////////////////////////////////////////
	DEBUGMSG();
	/////////////////////////////////////////////////////////

	// StringTools.h ////////////////////////////////////////
	cout << KappaTools::parse<int>("123") << " " << KappaTools::parse<double>("1.23") << endl;
	cout << KappaTools::parse<bool>("yes") << " " << KappaTools::parse<bool>("false") << endl;
	cout << KappaTools::str("TEST1") << " " << KappaTools::str(string("TEST2")) << endl;
	cout << KappaTools::str(123) << " " << KappaTools::str(1.23) << endl;
	/////////////////////////////////////////////////////////
	string s = "TesT";
	cout << KappaTools::startswith("Hallo Welt", "Hallo") << " - ";
	cout << KappaTools::startswith("Hallo Welt", "Welt") << " - ";
	cout << KappaTools::endswith("Hallo Welt", "Hallo") << " - ";
	cout << KappaTools::endswith("Hallo Welt", "Welt") << endl;
	cout << KappaTools::tolower(s) << " " << KappaTools::toupper(s) << endl;
	/////////////////////////////////////////////////////////

	// IOHelper.h ///////////////////////////////////////////
	map<int, string> mis;
	mis[1] = "A"; mis[2] = "B"; mis[123] = "ABC";
	cout << mis << endl;
	/////////////////////////////////////////////////////////
	set<double> sd;
	sd.insert(1.2); sd.insert(3.4); sd.insert(5.6);
	cout << sd << endl;
	/////////////////////////////////////////////////////////
	vector<string> vs;
	vs.push_back("A.2"); vs.push_back("B.4"); vs.push_back("C.6");
	cout << vs << endl;
	/////////////////////////////////////////////////////////
	cout << KappaTools::str<string>("123456") << endl;
	string tmp = KappaTools::join(".-.", sd);
	cout << tmp << endl;
	/////////////////////////////////////////////////////////
	cout << strmap(myconv, sd) << endl;
	cout << strmap(KappaTools::str<double>, sd) << endl;
	cout << mymap(myadd, sd) << endl;
	cout << strmap(myconv, mymap(myadd, sd)) << endl;
	cout << endl;
	/////////////////////////////////////////////////////////

	// VectorTools.h ////////////////////////////////////////
	map<std::string, int> redict;
	redict["Hello"] = 1;
	redict["World"] = 2;
	redict["Test"] = 3;
	redict["Entry"] = 4;
	redict["Entries"] = 5;
#ifdef HAS_BOOST_LIB
	cout << match("e", redict) << endl;
	cout << match("e|l", redict) << endl;
	cout << match("Entr.*", redict) << endl;
#endif
	/////////////////////////////////////////////////////////

	return 0;
}
