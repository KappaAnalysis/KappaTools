#include "BalancePtCut.h"

namespace KappaTools
{
	template <typename T1, typename T2>
	BalancePtCut<T1, T2>::BalancePtCut() : BaseCut("pt bal. cut")
	{
		obj1.clear();
		obj2.clear();
		mode = 0;
		min = -100.;
		max = 100.;
	}

	template <typename T1, typename T2>
	void BalancePtCut<T1, T2>::setCut(double cut_)
	{
		min = -1. * std::abs(cut_);
		max =       std::abs(cut_);
	}

	template <typename T1, typename T2>
	void BalancePtCut<T1, T2>::setMinCut(double min_)
	{
		min = min_;
	}

	template <typename T1, typename T2>
	void BalancePtCut<T1, T2>::setMaxCut(double max_)
	{
		max = max_;
	}

	template <typename T1, typename T2>
	void BalancePtCut<T1, T2>::setPointer1(T1 * tmpObj)
	{
		obj1.clear();
		obj1.push_back(tmpObj);
	}

	template <typename T1, typename T2>
	void BalancePtCut<T1, T2>::setPointer2(T2 * tmpObj)
	{
		obj2.clear();
		obj2.push_back(tmpObj);
	}

	template <typename T1, typename T2>
	void BalancePtCut<T1, T2>::addPointer1(T1 * tmpObj)
	{
		obj1.push_back(tmpObj);
	}

	template <typename T1, typename T2>
	void BalancePtCut<T1, T2>::addPointer2(T2 * tmpObj)
	{
		obj2.push_back(tmpObj);
	}

	template <typename T1, typename T2>
	void BalancePtCut<T1, T2>::setMode(unsigned int mode_)
	{
		mode = mode_;
	}

	template <typename T1, typename T2>
	bool BalancePtCut<T1, T2>::getInternalDecision()
	{
		if (obj1.size()==0 || obj2.size()==0)
			return false;
	
		double val = getDecisionValue();
	
		if (val>min && val<max)
			return true;
		else
			return false;
	}

	template <typename T1, typename T2>
	double BalancePtCut<T1, T2>::getDecisionValue()
	{
		if (obj1.size()==0 || obj2.size()==0)
			return -1.;
		
		RMLV sum1;
		RMLV sum2;
	
		for (typename std::vector<T1 *>::iterator it = obj1.begin(); it != obj1.end(); it++)
			sum1 += (*it)->p4;
		
		for (typename std::vector<T2 *>::iterator it = obj2.begin(); it != obj2.end(); it++)
			sum2 += (*it)->p4;
	
		switch (mode)
		{
			case AbsPtDiff:
				return sum1.pt()-sum2.pt();
				break;
			case RelPtDiff:
				return (sum1.pt()-sum2.pt())/sum1.pt();
				break;
			case PtRatio:
				return (sum1.pt()/sum2.pt());
				break;
			default:
				return -1.;
		}
	}
	template class BalancePtCut<KappaTools::ZmumuObjects<KDataJet, KDataMET>, KDataJet>;
	template class BalancePtCut<KappaTools::ZmumuObjects<KDataPFJet, KDataPFMET>, KDataPFJet>;
}
