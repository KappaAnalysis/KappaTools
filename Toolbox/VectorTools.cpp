#include "VectorTools.h"

using namespace std;

std::vector<int> seq(int last)
{
	std::vector<int> result;
	for (int i = 0; i <= last; ++i)
		result.push_back(i);
	return result;
}

std::vector<int> seq(int start, int last)
{
	std::vector<int> result;
	for (int i = start; i <= last; ++i)
		result.push_back(i);
	return result;
}
