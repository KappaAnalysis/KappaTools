#include "Kappa/DataFormats/interface/KMetadata.h"
#include "../RootTools/RunLumiReader.h"
#include "../RootTools/FileInterface.h"
#include "../Toolbox/CmdLineSetup.h"

using namespace std;

int main(int argc, char **argv)
{
	vector<string> files = CmdLineBase::ParseArgs(argc, argv, OPT_Help | OPT_Version);

	// Loading files
	FileInterface fi(files, false, 0);

	double xsec = 0;
	vector<pair<run_id, lumi_id> > lumis = fi.GetRunLumis();
	for (size_t l = 0; l < lumis.size(); ++l)
	{
		run_id run = lumis[l].first;
		lumi_id lumi = lumis[l].second;
		xsec += fi.Get<KGenLumiMetadata>(run, lumi)->xSectionInt;
	}
	cout << "Average xsec: " << xsec / lumis.size() << endl;

	const int nEvents = fi.eventdata.GetEntries();
	cout << "Number of events: " << nEvents << endl << endl;

	return 0;
}
