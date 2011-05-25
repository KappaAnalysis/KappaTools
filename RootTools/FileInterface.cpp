#include "FileInterface.h"

using namespace std;

namespace
{
	template<typename OutputIterator>
	OutputIterator GetListOfAllBranches(TBranch* branch, OutputIterator out)
	{
		TObjArray *lmBranch = branch->GetListOfBranches();
		for (int i = 0; i < lmBranch->GetEntries(); ++i)
		{
			TBranch* subbranch = dynamic_cast<TBranch*>(lmBranch->At(i));
			assert(subbranch != NULL);

			std::string name = lmBranch->At(i)->GetName();

			// Some hardcoded check because introspection of KDataLV does
			// not yield p4 but p4.fCoordinates.pt, p4.fCoordinates.eta
			// etc. directly.
			// TODO: A better way would probably be to do exactly that for
			// the TClass data members in FileInterface::GetInternal, if
			// possible (needs further investigation).
			if(name == "KDataLV")
				*out++ = "p4";
			else if(name == "covariance")
				*out++ = "covariance";
			else if(name == "position")
				*out++ = "position";
			else if(subbranch->IsFolder())
				out = GetListOfAllBranches(subbranch, out);
			else
				*out++ = lmBranch->At(i)->GetName();
		}

		return out;
	}
}

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
		}
		else
			if (cache > 0)
				eventdata.AddBranchToCache(b);
	}
}

void *FileInterface::GetInternal(TChain &chain, const char *cname, const std::string &name, const std::string altName)
{
	TBranch *branch = chain.GetBranch(name.c_str());
	std::string selected = "";
	if ((branch == 0) && (altName != "") && (chain.GetBranch(altName.c_str()) != 0))
		selected = altName;
	else if (branch != 0)
		selected = name;
	if (selected == "")
	{
		std::cerr << "Requested branch not found: " << name << std::endl;
		return 0;
	}

	branch = chain.GetBranch(selected.c_str());
	TClass *classRequest = TClass::GetClass(cname);
	TClass *classBranch = TClass::GetClass(branch->GetClassName());

	// Check inheritance of requested object
	if (!classBranch->InheritsFrom(classRequest))
	{
		std::cerr << "Incompatible types! Requested: " << classRequest->GetName()
			<< " Found: " << classBranch->GetName() << std::endl;
		return 0;
	}
	// Check members of requested object
	std::set<std::string> membersBranch, membersDict, membersDifference;
	GetListOfAllBranches(branch, std::inserter(membersBranch, membersBranch.begin()));
	TList *lmDict = classBranch->GetListOfAllPublicDataMembers();
	for (int i = 0; i < lmDict->GetEntries(); ++i)
		membersDict.insert(lmDict->At(i)->GetName());
	set_symmetric_difference(
		membersBranch.begin(), membersBranch.end(),
		membersDict.begin(), membersDict.end(),
		inserter(membersDifference, membersDifference.begin()));
	// This check does not yet work with vector and KVertexSummary
	if (string(classBranch->GetName()) != "KVertexSummary" && (string(classBranch->GetName()).find("vector") == std::string::npos) && membersDifference.size())
	{
		cerr << "Dictionary is not consistent with file content!" << endl;
		cerr << "Branch content: " << membersBranch << endl;
		cerr << "  Dict content: " << membersDict << endl;
		return 0;
	}
	// Allocate correct instance and set pointer
	void *tmp = classBranch->New();
	vBranchHolder.push_back(tmp);
	chain.SetBranchAddress(selected.c_str(), &(vBranchHolder.back()));
	return tmp;
}

bool FileInterface::isCompatible(unsigned int minRun, unsigned int maxRun)
{
	if (isMC)
	{
		for (std::map<std::pair<run_id, lumi_id>, KGenLumiMetadata>::const_iterator it = lumimap_mc.begin(); it != lumimap_mc.end(); ++it)
			if ((it->first.first >= minRun || minRun == 0) && (it->first.first <= maxRun || maxRun == 0))
				return true;
	}
	else
	{
		for (std::map<std::pair<run_id, lumi_id>, KLumiMetadata>::const_iterator it = lumimap_data.begin(); it != lumimap_data.end(); ++it)
			if ((it->first.first >= minRun || minRun == 0) && (it->first.first <= maxRun || maxRun == 0))
				return true;
	}
	return false;
}

std::vector<std::pair<run_id, lumi_id> > FileInterface::GetRunLumis() const
{
	std::vector<std::pair<run_id, lumi_id> > result;
	if (isMC)
		for (std::map<std::pair<run_id, lumi_id>, KGenLumiMetadata>::const_iterator it = lumimap_mc.begin(); it != lumimap_mc.end(); ++it)
			result.push_back(it->first);
	else
		for (std::map<std::pair<run_id, lumi_id>, KLumiMetadata>::const_iterator it = lumimap_data.begin(); it != lumimap_data.end(); ++it)
			result.push_back(it->first);
	return result;
}
