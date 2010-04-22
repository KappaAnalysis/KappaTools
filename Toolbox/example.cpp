#define DEBUG
#include "libKToolbox.h"
#include <iostream>
#include <iterator>

using namespace std;

double myadd(const double &x) { return x + 12.5; }
std::string myconv(const double &x) { return "XXX" + str(x); }

int main(int argc, char **argv)
{
	// Debug.h //////////////////////////////////////////////
	DEBUGMSG();
	/////////////////////////////////////////////////////////

	// StringTools.h ////////////////////////////////////////
	cout << parse<int>("123") << " " << parse<double>("1.23") << endl;
	cout << parse<bool>("yes") << " " << parse<bool>("false") << endl;
	cout << str("TEST1") << " " << str(string("TEST2")) << endl;
	cout << str(123) << " " << str(1.23) << endl;
	/////////////////////////////////////////////////////////
	string s = "TesT";
	cout << tolower(s) << " " << toupper(s) << endl;
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
	cout << str<string>("123456") << endl;
	string tmp = join(".-.", sd);
	cout << tmp << endl;
	/////////////////////////////////////////////////////////
	cout << strmap(myconv, sd) << endl;
	cout << strmap(str<double>, sd) << endl;
	cout << mymap(myadd, sd) << endl;
	cout << strmap(myconv, mymap(myadd, sd)) << endl;
	cout << endl;
	/////////////////////////////////////////////////////////

	return 0;
}
