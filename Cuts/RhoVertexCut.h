#ifndef KRhoVertexCut_h
#define KRhoVertexCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KBasic.h"

namespace KappaTools
{
	class RhoVertexCut : public BaseCut
	{
	private:
		KDataVertex * obj;
		double min;
		double max;
	public:
		RhoVertexCut();
		RhoVertexCut(KDataVertex * tmpObj);

		void setPointer(KDataVertex * tmpObj);

		void setMinCut(double min_);
		void setMaxCut(double max_);

		virtual bool getInternalDecision();
		double getDecisionValue();
	};
}

#endif
