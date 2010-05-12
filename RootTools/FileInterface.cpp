#include "FileInterface.h"

using namespace std;

FileInterface::FileInterface(vector<string> files, bool shuffle, int verbose) :
	eventdata("Events"), isMC(false), lumidata("Lumis"), verbosity(verbose)
{
	if (shuffle)
		random_shuffle(files.begin(), files.end());
	for (size_t i = 0; i < files.size(); ++i)
	{
		if (verbosity)
			cout << "Loading ... " << files[i] << endl;
		eventdata.Add(files[i].c_str());
		lumidata.Add(files[i].c_str());
	}

	TBranch *b = lumidata.GetBranch("KLumiMetadata");
	if (b)
		isMC = (string(b->GetClassName()) == "KGenLumiMetadata");
	if (verbosity)
		cout << endl << "Data source: " << (isMC ? "Monte-Carlo" : "Detector") << endl;

	if (isMC)
	{
		lumimap_mc = GetLumis<KGenLumiMetadata>();
		current_event = new KGenEventMetadata();
	}
	else
	{
		lumimap_data = GetLumis<KLumiMetadata>();
		current_event = new KEventMetadata();
	}
	eventdata.SetBranchAddress("KEventMetadata", &current_event);
}

KEventMetadata *FileInterface::GetEventMetadata()
{
	return current_event;
}

KGenEventMetadata *FileInterface::GetGenEventMetadata()
{
	if (!isMC)
		return 0;
	return static_cast<KGenEventMetadata*>(current_event);
}

void FileInterface::AssignEventPtr(KEventMetadata **meta_event, KGenEventMetadata **meta_event_gen)
{
	*meta_event = GetEventMetadata();
	if (meta_event_gen)
		*meta_event_gen = GetGenEventMetadata();
}

KLumiMetadata *FileInterface::GetLumiMetadata(run_id run, lumi_id lumi)
{
	return &(lumimap_mc[make_pair(run, lumi)]);
}

KGenLumiMetadata *FileInterface::GetGenLumiMetadata(run_id run, lumi_id lumi)
{
	if (!isMC)
		return 0;
	return static_cast<KGenLumiMetadata*>(GetLumiMetadata(run, lumi));
}

void FileInterface::AssignLumiPtr(run_id run, lumi_id lumi,
	KLumiMetadata **meta_lumi, KGenLumiMetadata **meta_lumi_gen)
{
	if (isMC)
	{
		*meta_lumi = &(lumimap_mc[make_pair(run, lumi)]);
		if (meta_lumi_gen)
			*meta_lumi_gen = static_cast<KGenLumiMetadata*>(*meta_lumi);
	}
	else
	{
		*meta_lumi = &(lumimap_data[make_pair(run, lumi)]);
		if (meta_lumi_gen)
			*meta_lumi_gen = 0;
	}
}

void FileInterface::SpeedupTree(long cache)
{
	if (cache > 0)
		eventdata.SetCacheSize(cache);
	TObjArray *branches = eventdata.GetListOfBranches();
	if (branches == 0)
		return;
	for (int i = 0; i < branches->GetEntries(); ++i)
	{
		TBranch *b = (TBranch*)branches->At(i);
		if (b->GetAddress() == 0)
		{
			UInt_t found = 0;
			string btype = b->GetClassName();
			string bname;
			if (btype.find("vector") == 0)
				bname = string(b->GetName()) + ".*";
			else
				bname = b->GetName();
			eventdata.SetBranchStatus(bname.c_str(), 0, &found);
			if (cache > 0)
				eventdata.AddBranchToCache(bname.c_str());
		}
	}
}
