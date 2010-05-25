#ifndef KMEToverSumEtCut_h
#define KMEToverSumEtCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KBasic.h"

namespace KappaTools
{
	template <typename METType>
	class METoverSumEtCut : public BaseCut
	{
		private:
			METType * obj;
			double min;
			double max;
		public:
			METoverSumEtCut() : BaseCut("MET/Et cut"), obj(0), min(0.), max(1.) {};
			METoverSumEtCut(METType * tmpObj) : BaseCut("MET/Et cut"), obj(tmpObj), min(0.), max(1.) {};

			void setPointer(METType * tmpObj);

			void setMinCut(double min_);
			void setMaxCut(double max_);

			virtual bool getInternalDecision();
			double getDecisionValue();
	};
}
#endif
