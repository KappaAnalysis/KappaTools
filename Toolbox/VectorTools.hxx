template<typename T>
std::vector<T> seq(T start, T inc, T last)
{
	std::vector<T> result;
	for (T i = start; i <= last; i += inc)
		result.push_back(i);
	return result;
}

template<typename Tlambda, typename Tin>
std::vector<std::string> strmap(const Tlambda &lambda, const Tin &list)
{
	std::vector<std::string> result;
	result.reserve(list.size());
	for (typename Tin::const_iterator it = list.begin(); it != list.end(); ++it)
		result.push_back(lambda(*it));
	return result;
}

template<typename Tin>
std::vector<std::string> fmtmap(const std::string &pattern, const Tin &list, const std::string &param)
{
	std::vector<std::string> result;
	result.reserve(list.size());
	for (typename Tin::const_iterator it = list.begin(); it != list.end(); ++it)
		result.push_back(replaceall(pattern, param, str(*it)));
	return result;
}

template<typename Tlambda, typename Tin>
Tin mymap(const Tlambda &lambda, const Tin &list)
{
	Tin result;
	for (typename Tin::const_iterator it = list.begin(); it != list.end(); ++it)
		result.insert(result.end(), lambda(*it));
	return result;
}

template<typename Tin>
std::string join(const std::string delim, const Tin &cont)
{
	if (cont.empty())
		return "";
	std::string result;
	typename Tin::const_iterator last = cont.end();
	for (typename Tin::const_iterator it = cont.begin(); it != cont.end();)
	{
		result += str(*it);
		if (++it != last)
			result += delim;
	}
	return result;
}

template<typename Tin, typename Tp1>
std::vector<Tp1> getFirst(const Tin &in)
{
	std::vector<Tp1> result;
	result.reserve(in.size());
	for (typename Tin::const_iterator it = in.begin(); it != in.end(); ++it)
		result.push_back(it->first);
	return result;
}

template<typename Tin, typename Tp1>
std::vector<Tp1> getSecond(const Tin &in)
{
	std::vector<Tp1> result;
	result.reserve(in.size());
	for (typename Tin::const_iterator it = in.begin(); it != in.end(); ++it)
		result.push_back(it->second);
	return result;
}

template<typename Tin, typename Tout>
Tout convert(const Tin &in)
{
	Tout result;
	for (typename Tin::const_iterator it = in.begin(); it != in.end(); ++it)
		result.insert(result.end(), (typename Tout::value_type)*it);
	return result;
}
