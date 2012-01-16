#include "FileInterfaceBase.h"

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
			if (name == "KDataLV")
				*out++ = "p4";
			else if (name == "covariance")
				*out++ = "covariance";
			else if (name == "position")
				*out++ = "position";
			else if (subbranch->IsFolder())
				out = GetListOfAllBranches(subbranch, out);
			else
				*out++ = lmBranch->At(i)->GetName();
		}

		return out;
	}
}

FileInterfaceBase::FileInterfaceBase(int verbose) :
	lumiInfoType(STD), eventchain(0), verbosity(verbose)
{
}

void FileInterfaceBase::Init(TChain *_eventchain, FileInterfaceBase::DataType _lumiInfoType)
{
	eventchain = _eventchain;
	lumiInfoType = _lumiInfoType;
}

void FileInterfaceBase::SpeedupTree(long cache)
{
	if (cache > 0)
		eventchain->SetCacheSize(cache);
	TObjArray *branches = eventchain->GetListOfBranches();
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
			eventchain->SetBranchStatus(bname.c_str(), 0, &found);
		}
		else
			if (cache > 0)
				eventchain->AddBranchToCache(b);
	}
}

void *FileInterfaceBase::GetInternal(TChain *chain, const char *cname, const std::string &name, const std::string altName, const bool check)
{
	TBranch *branch = chain->GetBranch(name.c_str());
	std::string selected = "";
	if ((branch == 0) && (altName != "") && (chain->GetBranch(altName.c_str()) != 0))
		selected = altName;
	else if (branch != 0)
		selected = name;
	if (selected == "")
	{
		std::cerr << "Requested branch not found: " << name << std::endl;
		return 0;
	}
	// Allow multiple get requests
	if (objCache.count(selected))
		return objCache[selected];

	branch = chain->GetBranch(selected.c_str());
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
		cerr << "Dictionary for class " << cname << " is not consistent with file content!" << endl;
		cerr << "Branch content: " << membersBranch << endl;
		cerr << "  Dict content: " << membersDict << endl;
		return 0;
	}
	// Allocate correct instance and set pointer
	void *tmp = classBranch->New();
	vBranchHolder.push_back(tmp);
	chain->SetBranchAddress(selected.c_str(), &(vBranchHolder.back()));
	objCache[selected] = tmp;
	return tmp;
}

bool FileInterfaceBase::isMC() const
{
	return (lumiInfoType == GEN);
}

template<>
KEventMetadata *FileInterfaceBase::Get()
{
	return current_event;
}

template<>
KGenEventMetadata *FileInterfaceBase::Get()
{
	if (lumiInfoType == GEN)
		return static_cast<KGenEventMetadata*>(current_event);
	return 0;
}
