/* Copyright (c) 2012 - All Rights Reserved
 *   Fred Stober <stober@cern.ch>
 */

// Get lumi metadata objects
template<typename T>
T *FileInterface2::GetMeta(std::string name, const bool check, const bool def)
{
	if (name == "")
		name = TypeName<T>::name();
	T *result = static_cast<T*>(GetInternal(lumidata, meta_branches, TypeName<T>::name(), name, check));
	if ((result == nullptr) && def)
		return new T();
	return result;
}

template<typename T>
std::vector<std::string> FileInterface2::GetMetaNames(bool inherited)
{
	return TreeObjects(*lumidata, TypeName<T>::name(), inherited);
}

template<typename T>
std::map<std::string, T*> FileInterface2::GetMetaAll(bool inherited)
{
	std::map<std::string, T*> result;
	std::vector<std::string> names = GetMetaNames<T>(inherited);
	for (std::vector<std::string>::const_iterator it = names.begin(); it < names.end(); ++it)
		result[*it] = GetMeta<T>(*it);
	return result;
}

// Get lumi metadata objects - old style
template<typename T>
T *FileInterface2::Get(run_id run, lumi_id lumi)
{
	GetMetaEntry(run, lumi);
	return GetMeta<T>("lumiInfo");
}

template<typename T>
inline T *FileInterface2::Get(KEventInfo *info_event)
{
	GetMetaEntry(info_event->nRun, info_event->nLumi);
	return GetMeta<T>("lumiInfo");
}
