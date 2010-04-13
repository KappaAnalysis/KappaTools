#ifndef TBVECTORTOOLS_H
#define TBVECTORTOOLS_H

#include <string>
#include <iostream>
#include <iterator>
#include <vector>

std::vector<int> seq(int last);
std::vector<int> seq(int start, int last);
template<typename T>
std::vector<T> seq(T start, T inc, T last);

template<typename Tlambda, typename Tin>
std::vector<std::string> strmap(const Tlambda &lambda, const Tin &list)
{
	std::vector<std::string> tmp;
	for (typename Tin::const_iterator it = list.begin(); it != list.end(); ++it)
		tmp.insert(tmp.end(), lambda(*it));
	return tmp;
}

template<typename Tlambda, typename Tin>
Tin mymap(const Tlambda &lambda, const Tin &list)
{
	Tin tmp;
	for (typename Tin::const_iterator it = list.begin(); it != list.end(); ++it)
		tmp.insert(tmp.end(), lambda(*it));
	return tmp;
}

template<typename Tin>
std::string join(const std::string delim, const Tin &cont)
{
	if (cont.empty())
		return "";
	std::string tmp;
	typename Tin::const_iterator last = cont.end();
	for (typename Tin::const_iterator it = cont.begin(); it != cont.end();)
	{
		tmp += str(*it);
		if (++it != last)
			tmp += delim;
	}
	return tmp;
}

#include "VectorTools.hxx"

#endif
