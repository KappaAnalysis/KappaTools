#ifndef KIsolationCut_h
#define KIsolationCut_h

#include "BaseCut.h"

namespace KappaTools
{
	template <typename T>
	class IsolationCut : public BaseCut
	{
		private:
			T * obj;
			double min;
			double max;
			double coneSize;
			char isoType;
		public:
			const static char TRACKISO = 0;
			const static char ECALISO  = 1;
			const static char HCALISO  = 2;

			IsolationCut();
			IsolationCut(T * tmpObj);

			void setPointer(T * tmpObj);

			void setConeSize(double min_);
			void setMinCut(double min_);
			void setMaxCut(double max_);

			virtual bool getInternalDecision();

			double getDecisionValue();
	};

	template <typename T>
	IsolationCut<T>::IsolationCut() : BaseCut("track iso cut"), obj(0), min(0.), max(1.), coneSize(0.3), isoType(TRACKISO) {}

	template <typename T>
	IsolationCut<T>::IsolationCut(T * tmpObj) : BaseCut("track iso cut"), obj(tmpObj), min(0.), max(1.), coneSize(0.3), isoType(TRACKISO) {}

	template <typename T>
	void IsolationCut<T>::setPointer(T * tmpObj)
	{
		obj = tmpObj;
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

		if (isoType == TRACKISO)
		{
			if (coneSize == 0.3)
				return obj->trackIso03;
			if (coneSize == 0.5)
				return obj->trackIso05;
			if (coneSize == 0.6)
				return obj->trackIso06;
		}

		if (isoType == HCALISO)
		{
			if (coneSize == 0.3)
				return obj->hcalIso03;
			if (coneSize == 0.5)
				return obj->hcalIso05;
			if (coneSize == 0.6)
				return obj->hcalIso06;
		}

		if (isoType == ECALISO)
		{
			if (coneSize == 0.3)
				return obj->ecalIso03;
			if (coneSize == 0.5)
				return obj->ecalIso05;
			if (coneSize == 0.6)
				return obj->ecalIso06;
		}
		return -1;
	}
}
#endif

