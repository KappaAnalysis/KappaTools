#ifndef __Xstatic
#define __Xstatic
#endif

template <typename T>
static T parse(const std::string &s, bool fail)
{
	T x; char temp; std::istringstream str(s);
	if (!(str >> x) || (fail && str.get(temp)))
	{
		std::cerr << "Parse error: " << s;
		exit(0);
	}
	return x;
}

template <>
__Xstatic std::string parse<std::string>(const std::string &s, bool)
{
	return s;
}

template <>
__Xstatic bool parse<bool>(const std::string &s, bool)
{
	static const std::string s_true[] = {"true", "yes", "y", "1"};
	static const std::string s_false[] = {"false", "no", "n", "0"};

	const std::string tmp = tolower(s);
	for (size_t i = 0; i < sizeof(s_true) / sizeof(std::string); ++i)
		if (s_true[i] == tmp)
			return true;
	for (size_t i = 0; i < sizeof(s_false) / sizeof(std::string); ++i)
		if (s_false[i] == tmp)
			return false;
	std::cerr << "Parse error - invalid bool: " << s;
	return false;
} 

template <typename T>
static std::string str(const T &i)
{
	std::ostringstream str;
	str << i;
	return str.str();
}

template <>
__Xstatic std::string str<bool>(const bool &i)
{
	if (i)
		return "true";
	return "false";
}
