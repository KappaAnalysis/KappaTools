/* Copyright (c) 2010 - All Rights Reserved
 *   Fred Stober <stober@cern.ch>
 *   Manuel Zeise <zeise@cern.ch>
 */

#include "Kappa/DataFormats/interface/Kappa.h"
#include "Kappa/DataFormats/interface/KDebug.h"
#include "../Toolbox/libKToolbox.h"
#include "../RootTools/libKRootTools.h"
#include "../RootTools/FileInterface2.h"
#include "../RootTools/ScaleService.h"

using namespace std;

int main(int argc, char **argv)
{
	std::cout << "Loading files..." << std::endl;
	vector<string> files;
	for (int i = 1; i < argc; ++i)
		files.push_back(argv[i]);
	std::cout.flush();
	std::cout << files << endl;
	ScaleServiceFactory ssf;
	FileInterface2 fi(files, 0, false, 2, &ssf, "output");
	ssf.registerLF("Tmp.csv");
	ssf.finish(fi.GetEntries(), 1, 1);

	std::cout << "finished" << std::endl;
	vector<string> names = fi.GetNames<KLVs>();
	cout << names << endl << endl;
	if (names.size() == 0)
		return -1;

	KLVs *jets = fi.Get<KLVs>(names[0]);
	KBeamSpot *bs = fi.Get<KBeamSpot>("offlineBeamSpot");

	std::map<std::string, KLVs*> tomap;
	for (size_t i = 0; i < names.size(); ++i)
		tomap[names[i]] = fi.Get<KLVs>(names[i]);

	KEventMetadata *meta_event = fi.Get<KEventMetadata>();

//	long long nEvents = min((long long)3, fi.eventdata.GetEntries());
	long long nEvents = fi.eventdata.GetEntries();
	std::cout << nEvents << std::endl;
	ProgressMonitor pm(nEvents);
	fi.SpeedupTree();
	for (long long iEvent = 0; iEvent < nEvents; ++iEvent)
	{
		if (!pm.Update()) break;
		fi.eventdata.GetEntry(iEvent);

		static LSWatcher lsWatcher;
		if (lsWatcher.Changed(meta_event))
			cout << "Reading new lumi metadata!" << endl;
		KLumiMetadata *meta_lumi = fi.Get<KLumiMetadata>(meta_event);
		KGenLumiMetadata *meta_lumi_gen = fi.Get<KGenLumiMetadata>(meta_event);

		if (meta_event->bitsHLT == 0)
			continue;

		cout << "Event metadata: " << *meta_event << endl;
		if (meta_lumi_gen)
			cout << "Generator lumi metadata: " << *meta_lumi_gen;
		else
			cout << "Lumi metadata: " << *meta_lumi;
		cout << "Jets: " << jets->size() << " => " << *jets << endl;
		if (bs)
			cout << "Beamspot: " << *bs << endl << endl;
		for (std::map<std::string, KLVs*>::iterator it = tomap.begin(); it != tomap.end(); ++it)
		{
			if (it->second->size() > 0)
			{
				cout << it->first << " " << it->second->size() << endl;
				cout << *(it->second) << endl;
			}
		}
		for (size_t i = 0; i < meta_lumi->hltNames.size(); ++i)
			if (meta_event->bitsHLT & (1ul << i))
				cout << meta_lumi->hltNames[i] << " ";
		cout << endl;
		cout << "=========" << endl << endl;
	}

	return 0;
}
