#ifndef KNonFakeVertexCut_h
#define KNonFakeVertexCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KBasic.h"

namespace KappaTools
{
	class NonFakeVertexCut : public BaseCut
	{
		private:
			KDataVertex * obj;
		public:
			NonFakeVertexCut();
			NonFakeVertexCut(KDataVertex * tmpObj);
			
			void setPointer(KDataVertex * tmpObj);
			
			virtual bool getInternalDecision();
			double getDecisionValue();
	};
}
#endif
