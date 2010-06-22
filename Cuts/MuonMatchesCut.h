#ifndef KMuonMatchesCut_h
#define KMuonMatchesCut_h

#include "TMath.h"
#include "BaseCut.h"
#include "DataFormats/interface/KMuon.h"

namespace KappaTools
{
	class MuonMatchesCut : public BaseCut
	{
		private:
			KDataMuon * obj;
			double min, max;
		public:
			MuonMatchesCut();
			MuonMatchesCut(KDataMuon * tmpObj);

			void setPointer(KDataMuon * tmpObj);

			void setMinCut(double min_);
			void setMaxCut(double max_);

			virtual bool getInternalDecision();
			double getDecisionValue();
	};
}

#endif
