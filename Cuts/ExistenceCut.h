#ifndef KExistenceCut_h
#define KExistenceCut_h

#include "BaseCut.h"
#include "Kappa/DataFormats/interface/KBasic.h"

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
}

#endif
