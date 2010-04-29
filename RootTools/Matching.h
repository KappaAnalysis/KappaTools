#ifndef KAPPA_MATCHING_H
#define KAPPA_MATCHING_H

#include <Math/VectorUtil.h>

using namespace std;

template<typename T1, typename T2>
std::vector<int> matchSort_Matrix(const std::vector<T1> &base, const size_t base_size,
	const std::vector<T2> &target, const size_t target_size)
{
	using namespace ROOT::Math;
	using namespace ROOT::Math::VectorUtil;

	double **match_metric = 0;
	std::vector<int> result(target_size, -1);
	static const double invalid = 1e10;

	// Build m x n Matrix with dR
	match_metric = new double*[base_size];
	for (unsigned int i = 0; i < base_size; ++i)
	{
		const T1 &jet_i = base[i];
		match_metric[i] = new double[target_size];
		for (unsigned int j = 0; j < target_size; ++j)
		{
			const T2 &jet_j = target[j];
			const double dR = DeltaR(jet_i.lv, jet_j.lv);
			if (dR < 1)
				match_metric[i][j] = dR;
			else
				match_metric[i][j] = invalid;
		}
	}

	// Find matching index
	for (unsigned int t = 0; t < target_size; ++t)
	{
//		PrintMatrix(match_metric, base_size, target_size);
		int best_i = -1, best_j = -1;
		double best_m = invalid;
		for (unsigned int i = 0; i < base_size; ++i)
			for (unsigned int j = 0; j < target_size; ++j)
			{
				const double m = match_metric[i][j];
				if (m < best_m)
				{
					best_i = i; best_j = j; best_m = m;
				}
			}
		if ((best_i == -1) || (best_j == -1))
			return result;
		for (unsigned int i = 0; i < base_size; ++i)
			match_metric[i][best_j] = invalid;
		for (unsigned int j = 0; j < target_size; ++j)
			match_metric[best_i][j] = invalid;
		if (best_i < invalid - 1)
			result[best_j] = best_i;
	}

	for (unsigned int i = 0; i < base_size; ++i)
		delete [] match_metric[i];
	delete [] match_metric;

	return result;
}

template<typename T1, typename T2>
void displayMatching(const T1 *jetsGen, const T2 *jetsCalo, const std::vector<int> &match)
{
	cout << "===========" << endl;
	displayLVs(*jetsGen);
	cout << "----" << endl;
	displayLVs(*jetsCalo);
	cout << "----" << endl;
	for (size_t j = 0; j < match.size(); ++j)
	{
		const int k = match[j];
		cout << j << "->" << k << "\t";
		if (k < 0)
		{
			cout << endl;
			continue;
		}
		cout << jetsCalo->at(k).lv << " -> " << jetsGen->at(j).lv << endl;
	}
}

#endif
