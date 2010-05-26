#include "DeltaRCut.h"

namespace KappaTools
{
	template <typename T1, typename T2>
	DeltaRCut<T1, T2>::DeltaRCut() : BaseCut("deltaR cut"), obj1(0), obj2(0), dR_min(0), dR_max(1e4) {}
	
	template <typename T1, typename T2>
	void DeltaRCut<T1, T2>::setPointer(T1 * tmpObj1, T2 * tmpObj2)
	{
		obj1=tmpObj1;
		obj2=tmpObj2;
	}
	
	template <typename T1, typename T2>
	void DeltaRCut<T1, T2>::setMinCut(double tmpdR_min)
	{
		dR_min = tmpdR_min;
	}
	
	template <typename T1, typename T2>
	void DeltaRCut<T1, T2>::setMaxCut(double tmpdR_max)
	{
		dR_max = tmpdR_max;
	}
	
	template <typename T1, typename T2>
	bool DeltaRCut<T1, T2>::getInternalDecision()
	{
		if (!obj1 || !obj2)
			return false;
		
		double dR = ROOT::Math::VectorUtil::DeltaR(obj1->p4, obj2->p4);
		return !(dR<dR_min || dR>dR_max);
	};
	
	template <typename T1, typename T2>
	double DeltaRCut<T1, T2>::getDecisionValue()
	{
		if (!obj1 || !obj2)
			return -1.;
		return ROOT::Math::VectorUtil::DeltaR(obj1->p4, obj2->p4);
	};
}
