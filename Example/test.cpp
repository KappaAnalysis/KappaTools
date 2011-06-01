#include "../Kappa/DataFormats/interface/Kappa.h"
#include "../Kappa/DataFormats/interface/KDebug.h"
#include "RootTools/FileInterface.h"
#include "Toolbox/IOHelper.h"

using namespace std;

int main(int argc, char **argv)
{
	FileInterface fi(vector<string>(1, argv[1]));

	vector<string> names = fi.GetNames<KDataLVs>();
	cout << names << endl << endl;
	if (names.size() == 0)
		return -1;
	KDataLVs *jets = fi.Get<KDataLVs>(names[0]);
	KDataBeamSpot *bs = fi.Get<KDataBeamSpot>("offlineBeamSpot");

	KEventMetadata *meta_event = fi.Get<KEventMetadata>();
//	KGenEventMetadata *meta_event_gen = fi.Get<KGenEventMetadata>();

	long long nEvents = min((long long)3, fi.eventdata.GetEntries());
	ProgressMonitor pm(nEvents);
	for (long long iEvent = 0; iEvent < nEvents; ++iEvent)
	{
		if (!pm.Update()) break;
		fi.eventdata.GetEntry(iEvent);

		KLumiMetadata *meta_lumi = fi.Get<KLumiMetadata>(meta_event->nRun, meta_event->nLumi);
		KGenLumiMetadata *meta_lumi_gen = fi.Get<KGenLumiMetadata>(meta_event->nRun, meta_event->nLumi);

		cout << "Event metadata: " << *meta_event << endl;
		if (meta_lumi_gen)
			cout << "Generator lumi metadata: " << *meta_lumi_gen;
		else
			cout << "Lumi metadata: " << *meta_lumi;
		cout << "Jets: " << jets->size() << " => " << *jets << endl;
		if (bs)
			cout << "Beamspot: " << *bs << endl << endl;
		cout << "=========" << endl << endl;
	}

	return 0;
}
