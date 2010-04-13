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
