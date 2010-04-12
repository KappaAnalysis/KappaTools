#include "Version.h"
#include "IOHelper.h"

using namespace std;

map<string, string> VersionInfo::versions;

VersionInfo::VersionInfo(string subsystem, string version)
{
	VersionInfo::versions[subsystem] = version;
}

void VersionInfo::print(ostream &os)
{
	OStreamGuard guard(os);
	size_t w = 0;
	for (map<string, string>::const_iterator it = versions.begin();
		it != versions.end(); ++it)
		w = max(it->first.size(), w);

	for (map<string, string>::const_iterator it = versions.begin();
		it != versions.end(); ++it)
		os << "\t" << setw(w) << it->first << ": " << it->second << endl;
}
