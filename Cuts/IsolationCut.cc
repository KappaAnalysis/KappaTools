#include "IsolationCut.h"

namespace KappaTools
{
	template <typename T>
	IsolationCut<T>::IsolationCut() : BaseCut("track iso cut"), obj(0), min(0.), max(1.), coneSize(0.3), isoType(SUMPTISO), pileUpSubstraction(false) {}

	template <typename T>
	IsolationCut<T>::IsolationCut(T * tmpObj) : BaseCut("track iso cut"), obj(tmpObj), min(0.), max(1.), coneSize(0.3), isoType(SUMPTISO), pileUpSubstraction(false) {}

	template <typename T>
	IsolationCut<T>::IsolationCut(unsigned char type_, double coneSize_) : BaseCut("track iso cut"), obj(0), min(0.), max(1.), coneSize(coneSize_), isoType(type_), pileUpSubstraction(false) {}

#ifdef KAPPA_FEATURE_JETAREA
	template <typename T>
	void IsolationCut<T>::setPointer(T * tmpObj, KJetArea * tmpJetAreaInfo)
	{
		obj = tmpObj;
		jetAreaInfo = tmpJetAreaInfo;
	}
#else
	template <typename T>
	void IsolationCut<T>::setPointer(T * tmpObj)
	{
		obj = tmpObj;
	}
#endif

	template <typename T>
	void IsolationCut<T>::setType(unsigned char isoType_)
	{
		isoType = isoType_;
	}


	template <typename T>
	void IsolationCut<T>::setConeSize(double coneSize_)
	{
		coneSize = coneSize_;
	}

	template <typename T>
	void IsolationCut<T>::setMinCut(double min_)
	{
		min = min_;
	}

	template <typename T>
	void IsolationCut<T>::setMaxCut(double max_)
	{
		max = max_;
	}

#ifdef KAPPA_FEATURE_JETAREA
	template <typename T>
	void IsolationCut<T>::setPUSubstraction(bool pileUpSubstraction_)
	{
		pileUpSubstraction = pileUpSubstraction_;
	}
#endif

	template <typename T>
	bool IsolationCut<T>::getInternalDecision()
	{
		if (!obj)
			return false;

		double val = getDecisionValue();

		return (val >= min && val <= max);
	}

	template <typename T>
	double IsolationCut<T>::getDecisionValue()
	{
		if (!obj)
			return -1;

		double retValue = -1.;
		if (isoType == TRACKISO)
		{
			if (coneSize == 0.3)
				retValue = obj->trackIso03;
			if (coneSize == 0.5)
				retValue = obj->trackIso05;
		}

		if (isoType == HCALISO)
		{
			if (coneSize == 0.3)
				retValue = obj->hcalIso03;
			if (coneSize == 0.5)
				retValue = obj->hcalIso05;
		}

		if (isoType == ECALISO)
		{
			if (coneSize == 0.3)
				retValue = obj->ecalIso03;
			if (coneSize == 0.5)
				retValue = obj->ecalIso05;
		}

		if (isoType == SUMPTISO)
		{
			if (coneSize == 0.3)
				retValue = obj->sumPtIso03;
			if (coneSize == 0.5)
				retValue = obj->sumPtIso05;
		}

		if (isoType == RELCOMBISO)
		{
			if (coneSize == 0.3)
				retValue = (obj->sumPtIso03 + obj->hcalIso03 + obj->ecalIso03) / obj->p4.pt();
			if (coneSize == 0.5)
				retValue = (obj->sumPtIso05 + obj->hcalIso05 + obj->ecalIso05) / obj->p4.pt();
		}

#ifdef KAPPA_FEATURE_JETAREA
		if ((isoType == SUMPTISO || isoType == RELCOMBISO) && !jetAreaInfo && pileUpSubstraction)
		{
			retValue -= (jetAreaInfo->median - jetAreaInfo->sigma) * coneSize * coneSize * 3.14159;
		}
#endif
		return std::max(retValue, 0.);
	}
}

template class KappaTools::IsolationCut<KDataMuon>;
