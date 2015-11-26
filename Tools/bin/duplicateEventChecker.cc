/* Copyright (c) 2010 - All Rights Reserved
 *   Andreas Oehler <andreasoehler@gmx.net>
 *   Fred Stober <stober@cern.ch>
 */

#include <set>
#include <TChain.h>
#include "../../Toolbox/interface/CmdLineSetup.h"
#include "../../Toolbox/interface/ProgressMonitor.h"
#include "../../RootTools/interface/EventLogger.h"
#include "../../RootTools/interface/FileInterface.h"
#include "Kappa/DataFormats/interface/KDebug.h"

using namespace std;

void MyHelpFunction(string arg)
{
	cout << "Duplicate Event Checker Help: " << endl;
	cout << CmdLineBase::basename << " [list of filenames] " << endl;
	exit(1);
}

int main(int argc, char* argv[])
{
	static CmdLineOptionCallback clHelp('h', "help", "Print help", MyHelpFunction);
	std::vector<std::string> filenames = CmdLineBase::ParseArgs(argc, argv);

	if (filenames.size() == 0)
	{
		cerr << "No input files given!" << endl;
		MyHelpFunction("");
	}
	cout << "Reading files: " << filenames << endl;
	cout << "\nDuplicate Event Checker " << endl;
	cout << "-- currently only checking for duplicate run/lumisection/event/BX numbers." << endl;
	cout << "Feel free to add physical event-checking for Generator etc. yourself, as this needs to be adopted to the specific sample. (Check Muon/Jet Pt, etc.)\n" << endl;

	FileInterface kpFi(filenames, false, 2);
	TChain &theChain = kpFi.eventdata;
	KEventInfo *metadata = kpFi.Get<KEventInfo>();
	EventLogger<std::set<EventID> > log;

	//now code the super-sophisticated event loop.
	const unsigned nEvents = theChain.GetEntries();
	ProgressMonitor pm(nEvents);
	for (unsigned i = 0;i < nEvents;++i)
	{
		if (!pm.Update()) break;
		theChain.GetEntry(i);
		if (log.has(metadata))
		{
			cerr << "Duplicate Event found!!! " << endl;
			cout << *metadata << endl;
			exit(1);
		}
		else
			log.put(metadata);
	}

	cout << "RESULT: No duplicate events found." << endl;
	return 0;
}
