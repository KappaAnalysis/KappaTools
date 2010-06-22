#include "TrackIPCut.h"

namespace KappaTools
{
	template <typename T>
	TrackIPCut<T>::TrackIPCut()	: BaseCut("trk IP cut"), obj(0), min(0), max(-1), type(TrackIPCut<T>::DXY) {}

	template <typename T>
	TrackIPCut<T>::TrackIPCut(T * tmpObj) : BaseCut("trk IP cut"), obj(tmpObj), min(0), max(-1), type(TrackIPCut<T>::DXY) {}

	template <typename T>
	TrackIPCut<T>::TrackIPCut(int type_) : BaseCut("trk IP cut"), obj(0), min(0), max(-1), type(type_) {}

	template <typename T>
	void TrackIPCut<T>::setPointer(T * tmpObj)
	{
		obj = tmpObj;
	}
	
	template <typename T>
	void TrackIPCut<T>::setPV(KDataVertex * tmpObj)
	{
		pv = tmpObj;
		bs = 0;
	}

	template <typename T>
	void TrackIPCut<T>::setBS(KDataBeamSpot * tmpObj)
	{
		pv = 0;
		bs = tmpObj;
	}

	template <typename T>
	void TrackIPCut<T>::setType(int type_)
	{
		type = type_;
	}

	template <typename T>
	void TrackIPCut<T>::setMinCut(double min_)
	{
		min = min_;
	}

	template <typename T>
	void TrackIPCut<T>::setMaxCut(double max_)
	{
		max = max_;
	}

	template <typename T>
	bool TrackIPCut<T>::getInternalDecision()
	{
		if (!obj)
			return false;

		double val = getDecisionValue();

		if (max==-1)
			return (val>min);
		else
			return (val>min && val<max);
	}

	template <typename T>
	double TrackIPCut<T>::getDecisionValue()
	{
		if (!obj || (!pv && !bs))
			return -1.;

		/*
			mode:
				0 - dxy
				1 - dxy/error(track)
				2 - dxy/sqrt(error(track)**2 + error(vertex)**2)
		*/
		switch(type)
		{
			case TrackIPCut::DXY:
				if (pv)
					return obj->getIP(pv, 0);
				else
					return obj->getIP(bs, 0);
			case TrackIPCut::DXY_ERRTRK:
				if (pv)
					return obj->getIP(pv, 1);
				else
					return obj->getIP(bs, 1);
			case TrackIPCut::DXY_ERRTRK_ERRVTX:
				if (pv)
					return obj->getIP(pv, 2);
				else
					return obj->getIP(bs, 2);
			default:
				return -1.;
		}
	}

	template class TrackIPCut<KDataTrack>;
}
