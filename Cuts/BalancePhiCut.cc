#include "BalancePhiCut.h"

namespace KappaTools
{
	template <typename T1, typename T2>
	BalancePhiCut<T1, T2>::BalancePhiCut() : BaseCut("phi bal. cut")
	{
		obj1.clear();
		obj2.clear();
		mode = 0;
		min = -100.;
		max = 100.;
	}

	template <typename T1, typename T2>
	void BalancePhiCut<T1, T2>::setCut(double cut_)
	{
		min = -1. * std::abs(cut_);
		max =       std::abs(cut_);
	}

	template <typename T1, typename T2>
	void BalancePhiCut<T1, T2>::setMinCut(double min_)
	{
		min = min_;
	}

	template <typename T1, typename T2>
	void BalancePhiCut<T1, T2>::setMaxCut(double max_)
	{
		max = max_;
	}

	template <typename T1, typename T2>
	void BalancePhiCut<T1, T2>::setPointer1(T1 * tmpObj)
	{
		obj1.clear();
		obj1.push_back(tmpObj);
	}

	template <typename T1, typename T2>
	void BalancePhiCut<T1, T2>::setPointer2(T2 * tmpObj)
	{
		obj2.clear();
		obj2.push_back(tmpObj);
	}

	template <typename T1, typename T2>
	void BalancePhiCut<T1, T2>::addPointer1(T1 * tmpObj)
	{
		obj1.push_back(tmpObj);
	}

	template <typename T1, typename T2>
	void BalancePhiCut<T1, T2>::addPointer2(T2 * tmpObj)
	{
		obj2.push_back(tmpObj);
	}

	template <typename T1, typename T2>
	void BalancePhiCut<T1, T2>::setMode(unsigned int mode_)
	{
		mode = mode_;
	}

	template <typename T1, typename T2>
	bool BalancePhiCut<T1, T2>::getInternalDecision()
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
	double BalancePhiCut<T1, T2>::getDecisionValue()
	{
		RMLV sum1;
		RMLV sum2;
	
		for (typename std::vector<T1 *>::iterator it = obj1.begin(); it != obj1.end(); it++)
			sum1 += (*it)->p4;
		
		for (typename std::vector<T2 *>::iterator it = obj2.begin(); it != obj2.end(); it++)
			sum2 += (*it)->p4;
	
		switch (mode)
		{
			case 0:
				return std::abs(ROOT::Math::VectorUtil::Phi_mpi_pi(ROOT::Math::VectorUtil::DeltaPhi(sum1,sum2)-M_PI));
				break;
			case 1:
				return ROOT::Math::VectorUtil::DeltaPhi(sum1,sum2);
				break;			
			default:
				return -1.;
		}
	}
	template class BalancePhiCut<KappaTools::ZmumuObjects<KDataJet, KDataMET>, KDataJet>;
	template class BalancePhiCut<KappaTools::ZmumuObjects<KDataPFJet, KDataPFMET>, KDataPFJet>;
}
