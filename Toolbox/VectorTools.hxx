template<typename T>
std::vector<T> seq(T start, T inc, T last)
{
	std::vector<T> result;
	for (T i = start; i <= last; i += inc)
		result.push_back(i);
	return result;
}
