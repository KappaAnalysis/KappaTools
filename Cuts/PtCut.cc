#include "PtCut.h"

namespace KappaTools
{
	template <typename T>
	PtCut<T>::PtCut()	: BaseCut("pT cut"), obj(0), pt_min(0.), pt_max(1e6) {}
	
	template <typename T>
	PtCut<T>::PtCut(T * tmpObj) : BaseCut("pT cut"), obj(tmpObj), pt_min(0.), pt_max(1e6) {}

	template <typename T>
	void PtCut<T>::setPointer(T * tmpObj)
	{
		obj = tmpObj;
	}
	
	template <typename T>
	void PtCut<T>::setMinCut(double pt_min_)
	{
		pt_min = pt_min_;
	}
	
	template <typename T>
	void PtCut<T>::setMaxCut(double pt_max_)
	{
		pt_max = pt_max_;
	}

	template <typename T>
	bool PtCut<T>::getInternalDecision()
	{
		if (!obj)
			return false;
		
		double val = getDecisionValue();
		return (val>pt_min && val<pt_max);
	};

	template <typename T>
	double PtCut<T>::getDecisionValue()
	{
		if (!obj)
			return -1.;
		else
			return obj->p4.pt();
	};
	
	template class PtCut<KDataMuon>;
	template class PtCut<KDataTau>;
	template class PtCut<KDataPFTau>;
	template class PtCut<KDataJet>;
	template class PtCut<KDataPFJet>;	
}
