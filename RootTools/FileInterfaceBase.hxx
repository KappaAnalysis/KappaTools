// Get event metadata objects
template<typename T>
T *FileInterfaceBase::Get()
{
	std::cerr << "Unsupported event metadata type: " << TypeName<T>::name() << std::endl;
	return 0;
}

template<>
KEventMetadata *FileInterfaceBase::Get();
template<>
KGenEventMetadata *FileInterfaceBase::Get();

// Get event content from files
template<typename T>
T *FileInterfaceBase::Get(const std::string &name, const bool check, const bool def)
{
	T *result = static_cast<T*>(GetInternal(eventchain, TypeName<T>::name(), name, "", check));
	if ((result == 0) && def)
		return new T();
	return result;
}

template<typename T>
T *FileInterfaceBase::Get(const std::string &name, const std::string altName, const bool check)
{
	return static_cast<T*>(GetInternal(eventchain, TypeName<T>::name(), name, altName, check));
}

template<typename T>
std::vector<std::string> FileInterfaceBase::GetNames(bool inherited)
{
	return TreeObjects(*eventchain, TypeName<T>::name(), inherited);
}

template<typename T>
std::map<std::string, T*> FileInterfaceBase::GetAll(bool inherited)
{
	std::map<std::string, T*> result;
	std::vector<std::string> names = GetNames<T>(inherited);
	for (std::vector<std::string>::const_iterator it = names.begin(); it < names.end(); ++it)
		result[*it] = Get<T>(*it);
	return result;
}
