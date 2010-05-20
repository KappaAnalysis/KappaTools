template <typename T>
T parse(const std::string &s, bool fail)
{
	T x; char temp; std::istringstream str(s);
	if (!(str >> x) || (fail && str.get(temp)))
	{
		std::cerr << "Parse error: " << s;
		exit(0);
	}
	return x;
}

template <typename T>
std::string str(const T &i)
{
	std::ostringstream str;
	str << i;
	return str.str();
}
