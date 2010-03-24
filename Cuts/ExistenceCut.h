#ifndef KExistenceCut_h
#define KExistenceCut_h

#include "BaseCut.h"

namespace KappaTools
{
	// this cut checks the existence of the given object
	template <typename T>
	class ExistenceCut : public BaseCut
	{
		private:
			T * obj;
		public:
			ExistenceCut();
			ExistenceCut(T * tmpObj);
			void setPointer(T * tmpObj);
			virtual bool getInternalDecision();
			double getDecisionValue();
	};

	template <typename T>
	ExistenceCut<T>::ExistenceCut() : BaseCut("existence cut"), obj(0) {}

	template <typename T>
	ExistenceCut<T>::ExistenceCut(T * tmpObj) : BaseCut("existence cut"), obj(tmpObj) {}

	template <typename T>
	void ExistenceCut<T>::setPointer(T * tmpObj)
	{
		obj=tmpObj;
	}

	template <typename T>
	bool ExistenceCut<T>::getInternalDecision()
	{
		return ( obj ? true : false );
	}

	template <typename T>
	double ExistenceCut<T>::getDecisionValue()
	{
		return ( obj ? 1. : 0.);
	}
}
#endif
