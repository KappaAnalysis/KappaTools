#include "FileInterface.h"

FileInterface::FileInterface(ivector<std::string> args, bool shuffle, int verbose) :
	eventdata("Events"), isMC(false), lumidata("Lumis"),
	verbosity(verbose), old_run(-1), old_lumi(-1)
{
	if (shuffle)
		random_shuffle(args.begin(), args.end());
	for (size_t i = 0; i < args.size(); ++i)
	{
		if (verbosity)
			cout << "Loading ... " << args[i] << endl;
		eventdata.Add(args[i].c_str());
		lumidata.Add(args[i].c_str());
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

void FileInterface::AssignEventPtr(KEventMetadata **meta_event, KGenEventMetadata **meta_event_gen)
{
	if (isMC)
	{
		*meta_event = current_event;
		if (meta_event_gen)
			*meta_event_gen = static_cast<KGenEventMetadata*>(current_event);
	}
	else
	{
		*meta_event = current_event;
		if (meta_event_gen)
			*meta_event_gen = 0;
	}
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

void FileInterface::SpeedupTree(TTree *tree)
{
	TObjArray *branches = tree->GetListOfBranches();
	for (int i = 0; i < branches->GetEntries(); ++i)
	{
		TBranch *b = (TBranch*)branches->At(i);
		if (b->GetAddress() == 0)
		{
			UInt_t found = 0;
			string btype = b->GetClassName();
			if (btype.find("vector") == 0)
				tree->SetBranchStatus(_S(b->GetName()) + ".*", 0, &found);
			else
				tree->SetBranchStatus(b->GetName(), 0, &found);
		}
	}
}
