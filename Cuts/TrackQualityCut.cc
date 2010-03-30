#include "TrackQualityCut.h"

// note:
//  TrackQualityBitmask is already a bit mask!!
//  (in contrast to reco::TrackBase::TrackQuality which is only
//   the bit position)
namespace KappaTools
{
	template <typename T>
	TrackQualityCut<T>::TrackQualityCut()	: BaseCut("track quality"), obj(0), mask(TrackQualityCut::highPurity) {}

	template <typename T>
	TrackQualityCut<T>::TrackQualityCut(T * tmpObj) : BaseCut("track quality"), obj(tmpObj), mask(TrackQualityCut::highPurity) {}

	template <typename T>
	void TrackQualityCut<T>::setPointer(T * tmpObj)
	{
		obj = tmpObj;
	}

	template <typename T>
	void TrackQualityCut<T>::setCut(int mask_)
	{
		mask = mask_;
	}

	template <typename T>
	bool TrackQualityCut<T>::getInternalDecision()
	{
		if (!obj)
			return false;

		double val = getDecisionValue();
		
		return (obj->quality & mask);
	}

	template <typename T>
	double TrackQualityCut<T>::getDecisionValue()
	{
		if (!obj)
			return -1.;
		
		return obj->quality;
	}
}
