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
	eventdata("Events"), lumiInfoType(STD), lumidata("Lumis"), verbosity(verbose)
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
	{
		if (string(b->GetClassName()) == "KGenLumiMetadata")
			lumiInfoType = GEN;
		if (string(b->GetClassName()) == "KLumiMetadata")
			lumiInfoType = STD;
		if (string(b->GetClassName()) == "KDataLumiMetadata")
			lumiInfoType = DATA;
	}

	switch (lumiInfoType)
	{
	case GEN:
		cout << endl << "Data source: Monte Carlo" << endl;
		lumimap_mc = GetLumis<KGenLumiMetadata>();
		current_event = new KGenEventMetadata();
		break;
	case STD:
		cout << endl << "Data source: default" << endl;
		lumimap_std = GetLumis<KLumiMetadata>();
		current_event = new KEventMetadata();
		break;
	case DATA:
		cout << endl << "Data source: Detector" << endl;
		lumimap_data = GetLumis<KDataLumiMetadata>();
		current_event = new KEventMetadata();
		break;
	}
	eventdata.SetBranchAddress("KEventMetadata", &current_event);
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
		TBranch *b = dynamic_cast<TBranch*>(branches->At(i));
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

void *FileInterface::GetInternal(TChain &chain, const char *cname, const std::string &name, const std::string altName, const bool check)
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
	// This check does not yet work with vector
	if ((string(classBranch->GetName()).find("vector") == std::string::npos) && membersDifference.size() && check)
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

bool FileInterface::isMC() const
{
	return (lumiInfoType == GEN);
}

template<typename T>
inline bool isCompatible(const std::map<std::pair<run_id, lumi_id>, T> &lumimap, unsigned int minRun, unsigned int maxRun)
{
	for (typename std::map<std::pair<run_id, lumi_id>, T>::const_iterator it = lumimap.begin(); it != lumimap.end(); ++it)
		if ((it->first.first >= minRun || minRun == 0) && (it->first.first <= maxRun || maxRun == 0))
			return true;
	return false;
}

bool FileInterface::isCompatible(unsigned int minRun, unsigned int maxRun)
{
	switch (lumiInfoType)
	{
	case GEN:
		return ::isCompatible(lumimap_mc, minRun, maxRun);
	case STD:
		return ::isCompatible(lumimap_std, minRun, maxRun);
	case DATA:
		return ::isCompatible(lumimap_data, minRun, maxRun);
	}
	return false;
}

template<typename T>
inline std::vector<std::pair<run_id, lumi_id> > GetRunLumis(const std::map<std::pair<run_id, lumi_id>, T> &lumimap)
{
	std::vector<std::pair<run_id, lumi_id> > result;
	for (typename std::map<std::pair<run_id, lumi_id>, T>::const_iterator it = lumimap.begin(); it != lumimap.end(); ++it)
		result.push_back(it->first);
	return result;
}

std::vector<std::pair<run_id, lumi_id> > FileInterface::GetRunLumis() const
{
	switch (lumiInfoType)
	{
	case GEN:
		return ::GetRunLumis(lumimap_mc);
	case STD:
		return ::GetRunLumis(lumimap_std);
	case DATA:
		return ::GetRunLumis(lumimap_data);
	}
	return std::vector<std::pair<run_id, lumi_id> >();
}

template<>
KEventMetadata *FileInterface::Get()
{
	return current_event;
}

template<>
KGenEventMetadata *FileInterface::Get()
{
	if (lumiInfoType == GEN)
		return static_cast<KGenEventMetadata*>(current_event);
	return 0;
}

template<>
KLumiMetadata *FileInterface::Get(run_id run, lumi_id lumi)
{
	switch (lumiInfoType)
	{
	case GEN:
		return &(lumimap_mc[std::make_pair(run, lumi)]);
	case STD:
		return &(lumimap_std[std::make_pair(run, lumi)]);
	case DATA:
		return &(lumimap_data[std::make_pair(run, lumi)]);
	}
	return 0;
}

template<>
KGenLumiMetadata *FileInterface::Get(run_id run, lumi_id lumi)
{
	if (lumiInfoType == GEN)
		return &(lumimap_mc[std::make_pair(run, lumi)]);
	return 0;
}

template<>
KDataLumiMetadata *FileInterface::Get(run_id run, lumi_id lumi)
{
	if (lumiInfoType == DATA)
		return &(lumimap_data[std::make_pair(run, lumi)]);
	return 0;
}
