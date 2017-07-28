/* Copyright (c) 2011 - All Rights Reserved
 *   Fred Stober <stober@cern.ch>
 */

#include "Kappa/DataFormats/interface/KInfo.h"
#include "../../RootTools/interface/RunLumiReader.h"
#include "../../RootTools/interface/FileInterface.h"
#include "../../Toolbox/interface/CmdLineSetup.h"

using namespace std;

int main(int argc, char **argv)
{
	vector<string> files = CmdLineBase::ParseArgs(argc, argv, OPT_Help);

	// Loading files
	FileInterface fi(files, false, 0);

	double xsec = 0;
	vector<pair<run_id, lumi_id> > lumis = fi.GetRunLumis();
	for (size_t l = 0; l < lumis.size(); ++l)
	{
		run_id run = lumis[l].first;
		lumi_id lumi = lumis[l].second;
		xsec += fi.Get<KGenRunInfo>(run, lumi)->xSectionInt;
	}
	cout << "Average xsec: " << xsec / lumis.size() << endl;

	const int nEvents = fi.eventdata.GetEntries();
	cout << "Number of events: " << nEvents << endl << endl;

	return 0;
}
