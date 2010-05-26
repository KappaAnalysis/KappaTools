#ifndef KzVertexCut_h
#define KzVertexCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KBasic.h"

namespace KappaTools
{
	class zVertexCut : public BaseCut
	{
		private:
			KDataVertex * obj;
			double min;
			double max;
		public:
			zVertexCut();
			zVertexCut(KDataVertex * tmpObj);
			
			void setPointer(KDataVertex * tmpObj);
				
			void setMinCut(double min_);
			void setMaxCut(double max_);
			
			virtual bool getInternalDecision();
			double getDecisionValue();
	};
}

#endif
