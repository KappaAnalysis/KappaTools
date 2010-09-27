#include "TrackHitsCut.h"

namespace KappaTools
{
	template <typename T>
	TrackHitsCut<T>::TrackHitsCut()	: BaseCut("track hits"), obj(0), min(0), max(-1), type(TrackHitsCut::nValidHits) {}

	template <typename T>
	TrackHitsCut<T>::TrackHitsCut(T * tmpObj) : BaseCut("track hits"), obj(tmpObj), min(0), max(-1), type(TrackHitsCut::nValidHits) {}

	template <typename T>
	TrackHitsCut<T>::TrackHitsCut(int type_) : BaseCut("track hits"), obj(0), min(0), max(-1), type(type_) {}

	template <typename T>
	void TrackHitsCut<T>::setPointer(T * tmpObj)
	{
		obj = tmpObj;
	}

	template <typename T>
	void TrackHitsCut<T>::setType(int type_)
	{
		type = type_;
	}
	template <typename T>
	void TrackHitsCut<T>::setMinCut(unsigned short min_)
	{
		min = min_;
	}

	template <typename T>
	void TrackHitsCut<T>::setMaxCut(unsigned short max_)
	{
		max = max_;
	}

	template <typename T>
	bool TrackHitsCut<T>::getInternalDecision()
	{
		if (!obj)
			return false;

		double val = getDecisionValue();

		if (max == -1)
			return (val >= min);
		else
			return (val >= min && val <= max);
	}

	template <typename T>
	double TrackHitsCut<T>::getDecisionValue()
	{
		if (!obj)
			return -1.;

		switch (type)
		{
			case TrackHitsCut::nPixelLayers:
				return obj->nPixelLayers;
			case TrackHitsCut::nStripLayers:
				return obj->nPixelLayers;
			case TrackHitsCut::nValidPixelHits:
				return obj->nValidPixelHits;
			case TrackHitsCut::nValidStripHits:
				return obj->nValidStripHits;
			case TrackHitsCut::nValidMuonHits:
				return obj->nValidMuonHits;
			case TrackHitsCut::nLostMuonHits:
				return obj->nLostMuonHits;
			case TrackHitsCut::nBadMuonHits:
				return obj->nBadMuonHits;
			case TrackHitsCut::nValidHits:
				return obj->nValidHits;
			case TrackHitsCut::nLostHits:
				return obj->nLostHits;
			case TrackHitsCut::nTrackerHits:
				return obj->nValidPixelHits + obj->nValidStripHits;
			default:
				return -1.;
		}
	}

	template class TrackHitsCut<KDataTrack>;
}
