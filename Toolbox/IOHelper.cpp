#include "IOHelper.h"

using namespace std;

OStreamGuard::OStreamGuard(ostream &_os) : os(_os)
{
	p = os.precision();
	w = os.width();
	flags = os.flags();
	f = os.fill();
}

OStreamGuard::~OStreamGuard()
{
	os.precision(p);
	os.width(w);
	os.flags(flags);
	os.fill(f);
}
