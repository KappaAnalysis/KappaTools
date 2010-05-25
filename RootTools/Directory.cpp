#include "Directory.h"

std::vector<std::string> DirObjects(const TDirectory *dir, std::string filter)
{
	std::vector<std::string> objects;
	TIter iter(dir->GetListOfKeys());
	while (TKey *key = (TKey*)iter())
	{
		if (filter == "")
			objects.push_back(key->GetName());
		else if (key->GetClassName() == filter)
			objects.push_back(key->GetName());
	}
	return objects;
}

std::vector<std::string> TreeObjects(TTree &chain, const std::string cname, const bool inherited)
{
	std::vector<std::string> result;
	TObjArray *branches = chain.GetListOfBranches();
	if (branches == 0)
		return result;
	TClass *req = TClass::GetClass(cname.c_str());
	std::string reqName = req->GetName();
	for (int i = 0; i < branches->GetEntries(); ++i)
	{
		TBranch *b = (TBranch*)branches->At(i);
		TClass *cur = TClass::GetClass(b->GetClassName());
		if ((cur == req) || (inherited && cur->InheritsFrom(req)))
			result.push_back(b->GetName());
	}
	return result;
}
