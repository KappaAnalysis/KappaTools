#include "EtaCut.h"

namespace KappaTools
{
	template <typename T>
	EtaCut<T>::EtaCut()	: BaseCut("eta cut"), obj(0), eta_min(0.), eta_max(1e6) {}

	template <typename T>
	EtaCut<T>::EtaCut(T * tmpObj) : BaseCut("eta cut"), obj(tmpObj), eta_min(0.), eta_max(1e6) {}

	template <typename T>
	void EtaCut<T>::setPointer(T * tmpObj)
	{
		obj = tmpObj;
	}

	template <typename T>
	void EtaCut<T>::setCut(double eta_max_)
	{
		eta_min = -1. * std::abs(eta_max_);
		eta_max = std::abs(eta_max_);
	}

	template <typename T>
	void EtaCut<T>::setMinCut(double eta_min_)
	{
		eta_min = eta_min_;
	}

	template <typename T>
	void EtaCut<T>::setMaxCut(double eta_max_)
	{
		eta_max = eta_max_;
	}

	template <typename T>
	bool EtaCut<T>::getInternalDecision()
	{
		if (!obj)
			return false;

		double val = getDecisionValue();
		return (val>eta_min && val<eta_max);
	};

	template <typename T>
	double EtaCut<T>::getDecisionValue()
	{
		if (!obj)
			return -1.;
		else
			return obj->p4.eta();
	};

	template class EtaCut<KDataMuon>;
	template class EtaCut<KDataTau>;
	template class EtaCut<KDataPFTau>;
	template class EtaCut<KDataJet>;
	template class EtaCut<KDataPFJet>;
}
