#include "METoverSumEtCut.h"

namespace KappaTools
{
	template <typename METType>
	void METoverSumEtCut<METType>::setPointer(METType * tmpObj)
	{
		obj = tmpObj;
	}

	template <typename METType>
	void METoverSumEtCut<METType>::setMinCut(double min_)
	{
		min = min_;
	}

	template <typename METType>
	void METoverSumEtCut<METType>::setMaxCut(double max_)
	{
		max = max_;
	}

	template <typename METType>
	bool METoverSumEtCut<METType>::getInternalDecision()
	{
		if (!obj)
			return false;

		double val = getDecisionValue();

		return (val > min && val < max);
	};

	template <typename METType>
	double METoverSumEtCut<METType>::getDecisionValue()
	{
		if (!obj)
			return -1.;

		return obj->p4.Et() / obj->sumEt;
	};
}
