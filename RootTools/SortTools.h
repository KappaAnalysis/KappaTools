#ifndef KAPPA_SORTTOOLS_H
#define KAPPA_SORTTOOLS_H

template<typename T>
struct KLVSorter_pt
{
	bool operator() (const T &a, const T &b) { return (a.p4.pt() > b.p4.pt()); };
};

template<typename T>
struct KLVSorter_E
{
	bool operator() (const T &a, const T &b) { return (a.p4.E() > b.p4.E()); };
};

template<typename T>
inline void sort_pt(std::vector<T> *v)
{
	std::sort(v->begin(), v->end(), KLVSorter_pt<T>());
}

#endif
