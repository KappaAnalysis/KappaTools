#ifndef KAPPA_DIRECTORY_H
#define KAPPA_DIRECTORY_H

#include <vector>
#include <map>
#include <TDirectory.h>
#include <TKey.h>

template<typename T>
std::vector<T*> DirObjects(const TDirectory *dir)
{
	std::vector<T*> objects;
	TIter iter(dir->GetListOfKeys());
	while (TKey *key = (TKey*)iter())
	{
		TObject *obj = key->ReadObj();
		if (obj->InheritsFrom(T::Class()))
			objects.push_back((T*)obj);
	}
	return objects;
}

template<typename T>
std::map<std::string, T*> DirObjectsMap(const TDirectory *dir)
{
	std::map<std::string, T*> objects;
	TIter iter(dir->GetListOfKeys());
	while (TKey *key = (TKey*)iter())
	{
		TObject *obj = key->ReadObj();
		if (obj->InheritsFrom(T::Class()))
			objects[key->GetName()] = (T*)obj;
	}
	return objects;
}

std::vector<std::string> DirObjects(const TDirectory *dir, std::string filter);

#endif
