#ifndef KGoodTracksFractionCuts_h
#define KGoodTracksFractionCuts_h

#include "BaseCut.h"
#include <vector>
#include "DataFormats/interface/KTrack.h"

namespace KappaTools
{
	class GoodTracksFractionCut : public BaseCut
	{
		private:
			KDataTracks * obj;
			double min;
			double max;
			unsigned int goodTrackMask;
		public:
			GoodTracksFractionCut() : BaseCut("good track ratio"), obj(0), min(0.), max(1.), goodTrackMask(0) {};
			GoodTracksFractionCut(KDataTracks * tmpObj) : BaseCut("good track ratio"), obj(tmpObj), min(0.), max(1.), goodTrackMask(0) {};
		
			void setPointer(KDataTracks * tmpObj);
		
			void setGoodTrackMask(unsigned int tmp_);
			void setMinCut(double min_);
			void setMaxCut(double max_);
		
			virtual bool getInternalDecision();
			double getDecisionValue();
	};
}
#endif
