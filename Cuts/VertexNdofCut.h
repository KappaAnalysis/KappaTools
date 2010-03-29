#ifndef KVertexNdofCut_h
#define KVertexNdofCut_h

#include "BaseCut.h"
#include <vector>
#include "DataFormats/interface/KBasic.h"

namespace KappaTools
{
	class VertexNdofCut : public BaseCut
	{
		private:
			KDataVertex * obj;
			double min;
			double max;
		public:
			VertexNdofCut() : BaseCut("pv ndof cut"), obj(0), min(0.), max(1.) {};
			VertexNdofCut(KDataVertex * tmpObj) : BaseCut("pv ndof cut"), obj(tmpObj), min(0.), max(1.) {};
		
			void setPointer(KDataVertex * tmpObj);
			
			void setMinCut(double min_);
			void setMaxCut(double max_);
		
			virtual bool getInternalDecision();
			double getDecisionValue();
	};
}
#endif
