#include "../Kappa/DataFormats/interface/Kappa.h"
#include "../Kappa/DataFormats/interface/KDebug.h"
#include "RootTools/FileInterface.h"

using namespace std;

int main(int argc, char **argv)
{
	FileInterface fi(vector<string>(1, argv[1]));

	vector<string> names = fi.GetNames<KDataLVs>();
	cout << names << endl << endl;
	KDataLVs *jets = fi.Get<KDataLVs>(names[0]);
	KDataBeamSpot *bs = fi.Get<KDataBeamSpot>("offlineBeamSpot");

	KEventMetadata *meta_event = 0;
	KGenEventMetadata *meta_event_gen = 0;
	fi.AssignEventPtr(&meta_event, &meta_event_gen);

	long long nEvents = min((long long)3, fi.eventdata.GetEntries());
	ProgressMonitor pm(nEvents);
	for (long long iEvent = 0; iEvent < nEvents; ++iEvent)
	{
		if (!pm.Update()) break;
		fi.eventdata.GetEntry(iEvent);

		KLumiMetadata *meta_lumi = 0;
		KGenLumiMetadata *meta_lumi_gen = 0;
		fi.AssignLumiPtr(meta_event->nRun, meta_event->nLumi, &meta_lumi, &meta_lumi_gen);

		cout << *meta_event << endl << *meta_lumi << *jets << endl << *bs << endl << endl;
	}

	return 0;
}
