template <typename T>
T parse(const std::string &s, bool fail)
{
	T x; char temp; std::istringstream str(s);
	if (!(str >> x) || (fail && str.get(temp)))
		reportParseError(s);
	return x;
}

template <typename T>
std::string str(const T &i)
{
	std::ostringstream str;
	str << i;
	return str.str();
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
