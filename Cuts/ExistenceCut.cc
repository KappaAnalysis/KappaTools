#include "ExistenceCut.h"

namespace KappaTools
{
	template <typename T>
	ExistenceCut<T>::ExistenceCut() : BaseCut("existence cut"), obj(0) {}

	template <typename T>
	ExistenceCut<T>::ExistenceCut(T * tmpObj) : BaseCut("existence cut"), obj(tmpObj) {}

	template <typename T>
	void ExistenceCut<T>::setPointer(T * tmpObj)
	{
		obj = tmpObj;
	}

	template <typename T>
	bool ExistenceCut<T>::getInternalDecision()
	{
		return (obj ? true : false);
	}

	template <typename T>
	double ExistenceCut<T>::getDecisionValue()
	{
		return (obj ? 1. : 0.);
	}

	template class ExistenceCut<KDataVertex>;
}
