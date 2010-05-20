#include "TrackChi2Cut.h"

namespace KappaTools
{
	template <typename T>
	TrackChi2Cut<T>::TrackChi2Cut()	: BaseCut("track hits"), obj(0), min(0), max(-1), type(TrackChi2Cut<T>::CHI2NORM) {}

	template <typename T>
	TrackChi2Cut<T>::TrackChi2Cut(T * tmpObj) : BaseCut("track hits"), obj(tmpObj), min(0), max(-1), type(TrackChi2Cut<T>::CHI2NORM) {}

	template <typename T>
	void TrackChi2Cut<T>::setPointer(T * tmpObj)
	{
		obj = tmpObj;
	}

	template <typename T>
	void TrackChi2Cut<T>::setType(unsigned char type_)
	{
		type = type_;
	}

	template <typename T>
	void TrackChi2Cut<T>::setMinCut(unsigned short min_)
	{
		min = min_;
	}

	template <typename T>
	void TrackChi2Cut<T>::setMaxCut(unsigned short max_)
	{
		max = max_;
	}

	template <typename T>
	bool TrackChi2Cut<T>::getInternalDecision()
	{
		if (!obj)
			return false;

		double val = getDecisionValue();

		if (max==-1)
			return (val>=min);
		else
			return (val>=min && val<=max);
	}

	template <typename T>
	double TrackChi2Cut<T>::getDecisionValue()
	{
		if (!obj)
			return -1.;

		switch(type)
		{
			case TrackChi2Cut::CHI2:
				return obj->chi2;
			case TrackChi2Cut::NDOF:
				return obj->nDOF;
			case TrackChi2Cut::CHI2NORM:
				return obj->chi2/obj->nDOF;
			case TrackChi2Cut::CHI2PROB:
				return TMath::Prob(obj->chi2, static_cast<int>(obj->nDOF));
			default:
				return -1.;
		}
	}

	template class TrackChi2Cut<KDataTrack>;
	template class TrackChi2Cut<KDataVertex>;
}
