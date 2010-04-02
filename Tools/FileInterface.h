#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>

#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include "ProgressMonitor.h"
#include <DataFormats/src/classes.h>

typedef unsigned long run_id;
typedef unsigned long lumi_id;

struct FileInterface
{
	FileInterface(ivector<std::string> files, bool shuffle = false, int verbose = 2);
	void AssignEventPtr(KEventMetadata **meta_event, KGenEventMetadata **meta_event_gen = 0);
	void AssignLumiPtr(run_id run, lumi_id lumi,
		KLumiMetadata **meta_lumi, KGenLumiMetadata **meta_lumi_gen = 0);
	void SpeedupTree(TTree *tree);

	TChain eventdata;
	bool isMC;

private:
	TChain lumidata;
	int verbosity;

	run_id old_run;
	lumi_id old_lumi;
	KLumiMetadata *current_lumi;
	KEventMetadata *current_event;

	map<pair<run_id, lumi_id>, KGenLumiMetadata> lumimap_mc;
	map<pair<run_id, lumi_id>, KLumiMetadata> lumimap_data;

	template<typename T>
	map<pair<run_id, lumi_id>, T> GetLumis()
	{
		OStreamGuard guard(cout);
		if (verbosity)
			cout << "Reading lumi sections: " << endl;

		// Connect to lumi tree
		T *meta_lumi = new T();
		lumidata.SetBranchAddress("KLumiMetadata", &meta_lumi);

		// Collect lumi infos
		map<pair<run_id, lumi_id>, T> result;
		map<run_id, pair<lumi_id, lumi_id> > run_start_end;
		if (lumidata.GetEntries() > 0)
		{
			ProgressMonitor pm(lumidata.GetEntries());
			for (int i = 0; i < lumidata.GetEntries(); ++i)
			{
				pm.Update();
				lumidata.GetEntry(i);
				result[make_pair(meta_lumi->nRun, meta_lumi->nLumi)] = *meta_lumi;
				if (verbosity > 2)
					cout << "(" << meta_lumi->nRun << ":" << meta_lumi->nLumi << ") ";

				// Determine start/end of lumi section for run
				if (run_start_end.find(meta_lumi->nRun) == run_start_end.end())
					run_start_end[meta_lumi->nRun] = make_pair((lumi_id)-1, 0);
				run_start_end[meta_lumi->nRun] = make_pair(
					min(run_start_end[meta_lumi->nRun].first, meta_lumi->nLumi),
					max(run_start_end[meta_lumi->nRun].second, meta_lumi->nLumi)
				);
			}
		}
		if (verbosity > 2)
			cout << endl << endl;
		cout << "Number of unique lumi sections in dataset: " << result.size() << endl;
		if (verbosity > 1)
		{
			cout << endl << "Lumi ranges:" << endl;
			for (map<run_id, pair<lumi_id, lumi_id> >::const_iterator it = run_start_end.begin();
				it != run_start_end.end(); ++it)
				cout << setw(8) << it->first << ": "
					<< setw(4) << it->second.first << " - "
					<< setw(4) << it->second.second  << endl;
			cout << endl;
		}
		return result;
	}
};
