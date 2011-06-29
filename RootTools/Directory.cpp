#include "Directory.h"

std::map<std::string, TObject*> GetDirObjectsMap(TDirectory *dir)
{
	std::map<std::string, TObject*> result;
	TIter iter_mem(dir->GetList());
	while (TObject *obj = dynamic_cast<TObject*>(iter_mem()))
		result[obj->GetName()] = obj;
	TIter iter_disk(dir->GetListOfKeys());
	while (TKey *key = dynamic_cast<TKey*>(iter_disk()))
		if (result[key->GetName()] == 0)
			result[key->GetName()] = key->ReadObj();
	return result;
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
		TBranch *b = dynamic_cast<TBranch*>(branches->At(i));
		TClass *cur = TClass::GetClass(b->GetClassName());
		if ((cur == req) || (inherited && cur->InheritsFrom(req)))
			result.push_back(b->GetName());
	}
	return result;
}
