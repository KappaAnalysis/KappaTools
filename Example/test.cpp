#include "Kappa/DataFormats/interface/Kappa.h"
#include "Kappa/DataFormats/interface/KDebug.h"
#include "../Toolbox/libKToolbox.h"
#include "../RootTools/libKRootTools.h"

using namespace std;

int main(int argc, char **argv)
{
	std::cout << "Loading files..." << std::endl;
	std::cout.flush();
	FileInterface fi(vector<string>(1, argv[1]));
	std::cout << "finished" << std::endl;
	vector<string> names = fi.GetNames<KDataLVs>();
	cout << names << endl << endl;
	if (names.size() == 0)
		return -1;

	KDataLVs *jets = fi.Get<KDataLVs>(names[0]);
	KDataBeamSpot *bs = fi.Get<KDataBeamSpot>("offlineBeamSpot");

	std::map<std::string, KDataLVs*> tomap;
	for (size_t i = 0; i < names.size(); ++i)
		tomap[names[i]] = fi.Get<KDataLVs>(names[i]);

	KEventMetadata *meta_event = fi.Get<KEventMetadata>();
//	KGenEventMetadata *meta_event_gen = fi.Get<KGenEventMetadata>();

//	long long nEvents = min((long long)3, fi.eventdata.GetEntries());
	long long nEvents = fi.eventdata.GetEntries();
	ProgressMonitor pm(nEvents);
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
		for (size_t i = 0; i < names.size(); ++i)
		{
			if (tomap[names[i]]->size() > 0)
			{
				cout << names[i] << " " << tomap[names[i]]->size() << endl;
				cout << *tomap[names[i]] << endl;
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
