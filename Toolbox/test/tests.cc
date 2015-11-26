#define DEBUG
//#include <cassert>
#include "../interface/libKToolbox.h"
#include <iostream>
#include <iterator>

using namespace std;


double myadd(const double &x) { return x + 12.5; }
std::string myconv(const double &x) { return "XXX" + KappaTools::str(x); }

std::string check(std::string cmd, std::string is, std::string should)
{
	return cmd + " = " + ((is == should) ? green : red) + is + reset;
}

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
		CmdLineBase::ParseArgs(argc, argv, OPT_Help);
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

	// Math.h ///////////////////////////////////////////////
	cout << sqr<int>(5) << " " << sqr<double>(1.5) << endl;
	/////////////////////////////////////////////////////////
	cout << min<int>(3, 2) << " " << min<int>(3, 2, 1) << " " << min<int>(1, 2, 3) << endl;
	cout << max<int>(3, 2) << " " << max<int>(3, 2, 1) << " " << max<int>(1, 2, 3) << endl;
	/////////////////////////////////////////////////////////
	pair<string, string> r1 = sround(make_pair(1.00123, 0.0001));
	cout << r1.first << " " << r1.second << endl;
	/////////////////////////////////////////////////////////

	// Memory.h /////////////////////////////////////////////
	MemoryPool<string> pool;
	cout << pool.AddObject("TEST_1") << endl;
	cout << pool.AddObject(new string("TEST_2")) << endl;
	pool.Cleanup();
	/////////////////////////////////////////////////////////
	int *p = new int(2);
//	assert(p != 0);
	cout << *p << endl;
	mydelete<int>(p);
//	assert(p == 0);
	/////////////////////////////////////////////////////////
//	p = new int(0);
	/////////////////////////////////////////////////////////
	vector<int*> intvec;
	intvec.push_back(new int(3));
	intvec.push_back(new int(2));
	intvec.push_back(new int(1));
	intvec.push_back(new int(0));
	mydelete_vector<int>(intvec);
	/////////////////////////////////////////////////////////

	// String.h /////////////////////////////////////////////
	cout << randomstr() << " " << randomstr("TEST") << endl;
	cout << KappaTools::parse<int>("123") << " " << KappaTools::parse<double>("1.23") << endl;
	cout << KappaTools::parse<bool>("yes") << " " << KappaTools::parse<bool>("false") << endl;
	cout << KappaTools::str("TEST1") << " " << KappaTools::str(string("TEST2")) << endl;
	cout << KappaTools::str(123) << " " << KappaTools::str(1.23) << endl;
	const double x = 1.23456;
	cout << str(x, 3) << " " << x << " " << KappaTools::str(x) << endl;
	/////////////////////////////////////////////////////////
	cout << _S() + "TEST " + 123 + " " + x + " " + true << endl;
	cout << _S("TEST ").SetPrecision(0) + x << " " << true << endl;
	cout << _S("TEST ").SetPrecision(-1) + x << " " << true << endl;
	string s = "TesT";
	cout << _S(s).SetPrecision(2) + " " + x << " " << true << endl;
	/////////////////////////////////////////////////////////
	cout << KappaTools::tolower(s) << " " << KappaTools::toupper(s) << endl;
	cout << KappaTools::replace(s, "Te", "Be") << endl;
	cout << KappaTools::replace(s + s, "Te", "Be") << endl;
	cout << KappaTools::replaceall(s + s, "Te", "Be") << endl;
	/////////////////////////////////////////////////////////
	const string t = "THIS*IS-A GOOD'*'TEST::FOR,THE TOKENIZER";
	cout << t << endl;
	vector<string> tok = KappaTools::tokenize(t, " :*");
	cout << tok.size();
	copy(tok.begin(), tok.end(), ostream_iterator<string>(cout, "\t"));
	cout << endl;
	tok = KappaTools::tokenize(t, " :*-,", true);
	copy(tok.begin(), tok.end(), ostream_iterator<string>(cout, "\t"));
	cout << endl;
	/////////////////////////////////////////////////////////
	cout << KappaTools::in('x', string("TEST")) << endl;
	cout << KappaTools::in('T', string("TEST")) << endl;
	cout << check("lstrip(\"TTTTEST\", \"TS\")", KappaTools::lstrip("TTTTEST", "TS"), "EST") << endl;
	cout << check("lstrip(\"TTTTEST\", \"ET\")", KappaTools::lstrip("TTTTEST", "ET"), "ST") << endl;
	cout << check("rstrip(\"TTTTEST\", \"TS\")", KappaTools::rstrip("TTTTEST", "TS"), "TTTTE") << endl;
	cout << check("rstrip(\"TTTTEST\", \"ET\")", KappaTools::rstrip("TTTTEST", "ET"), "TTTTES") << endl;
	cout << check("strip(\"TTTTEST\", \"TS\")", KappaTools::strip("TTTTEST", "TS"), "E") << endl;
	cout << check("strip(\"TTTTEST\", \"ET\")", KappaTools::strip("TTTTEST", "ET"), "S") << endl;
	/////////////////////////////////////////////////////////

	// Text.h ///////////////////////////////////////////////
	cout.flush();
	map<int, string> mis;
	mis[1] = "A"; mis[2] = "B"; mis[123] = "ABC";
	cout << mis << endl;
	cout << getFirst<map<int, string>, int>(mis) << endl;
	cout << getSecond<map<int, string>, string>(mis) << endl;
	cout.flush();
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
	cout << sd << endl;
	cout << convert<set<double>, vector<double> >(sd) << endl;
	/////////////////////////////////////////////////////////
	cout << strmap(myconv, sd) << endl;
	cout << strmap(KappaTools::str<double>, sd) << endl;
	cout << fmtmap(string("This is a double: $DOUBLE"), sd, string("$DOUBLE")) << endl;
	cout << KappaTools::join("...\n", fmtmap(string("double: $DOUBLE"), sd, string("$DOUBLE"))) << endl;
	cout << mymap(myadd, sd) << endl;
	cout << strmap(myconv, mymap(myadd, sd)) << endl;
	cout << endl;
	cout << endl;
	/////////////////////////////////////////////////////////

	// Vector.h /////////////////////////////////////////////
	ivector<string> v = (_V<string>(), "TEST_A", "TEST_B", s);
	cout << v << endl;
	cout << "v0.subset(-1) v0.subset(1) v0.subset(5) "
		<< "v0.subset(0,0) v0.subset(0,1) v0.subset(0,2) v0.subset(0,3)" << endl;
	ivector<int> v0 = seq(1, 3);
	cout << v0.subset(-1) << "  *  " << v0.subset(1) << "  *  " << v0.subset(5)
		<< "  *  " << v0.subset(0,0) << "  *  "  << v0.subset(0,1)
		<< "  *  "  << v0.subset(0,2) << "  *  "  << v0.subset(0,3) << endl;
	ivector<string>::delimeter = " -*- ";
	cout << v << endl;
	ivector<double> v1 = (_V<double>(1.1), 3.3, 5.5, 7.7);
	ivector<double> v2 = (_V<double>(2.2), 4.4, 6.6, 8.8);
	cout << (v1, v2) << endl;
	cout << (v1 & v2) << endl;
	cout << (v1 | v2) << endl;
	ivector<double>::delimeter = " => ";
	cout << (v1 | v2) << endl;
	ivector<int> v3 = _V<int>(1) & 2 & 3;
	ivector<int> v4 = _V<int>(10) & 20 & 30;
	cout << v3 * 2 << endl;
	cout << (v3 ^ 2) << endl;
	cout << v3 + 10 << endl;
	cout << (v3 | v4) << endl;
	cout << (v3 | v4) + v4 << endl;
	cout << v3 << " :: " << v4 << endl;
	v3 &= v4;
	cout << v3 << " :: " << v4 << endl;
	/////////////////////////////////////////////////////////
	ivector<string> v5 = _V("HALLO") & " ! " & "WELT";
	copy(v5.begin(), v5.end(), ostream_iterator<string>(cout, "\t"));
	cout << endl;
	vector<string> v6 = v5;
	copy(v6.begin(), v6.end(), ostream_iterator<string>(cout, "\t"));
	cout << endl;
	ivector<string> v7 = v6;
	copy(v7.begin(), v7.end(), ostream_iterator<string>(cout, "\t"));
	cout << endl;
	ivector<int> v8 = 12345;
	copy(v8.begin(), v8.end(), ostream_iterator<int>(cout, "\t"));
	cout << endl;
	/////////////////////////////////////////////////////////
	cout << v5.getreverse() << endl;
	ivector<ivector<int> > vv1 = _V(v3) & v4 & v8;
	cout << vv1 << endl;
	cout << Flatten(vv1) << endl;
	cout << Collect(vv1, 1) << endl;
	cout << Collect(vv1, 3) << endl;
	/////////////////////////////////////////////////////////
	cout << v5.has("HALLO") << " " << v5.has("HELLO") << endl;
	/////////////////////////////////////////////////////////

	return 0;
}
