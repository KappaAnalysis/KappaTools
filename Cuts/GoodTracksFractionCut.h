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
			KDataTracks * obj_Tracks;
			KTrackSummary * obj_TrackSummary;
			double min;
			double max;
			int numtracks;
			unsigned int goodTrackMask;
		public:
			GoodTracksFractionCut() : BaseCut("good track ratio"), obj_Tracks(0), obj_TrackSummary(0), min(0.), max(1.), numtracks(10), goodTrackMask(1 << 2) {};
			GoodTracksFractionCut(KDataTracks * tmpObj) : BaseCut("good track ratio"), obj_Tracks(tmpObj), obj_TrackSummary(0), min(0.), max(1.), numtracks(10), goodTrackMask(1 << 2) {};
			GoodTracksFractionCut(KTrackSummary * tmpObj) : BaseCut("good track ratio"), obj_Tracks(0), obj_TrackSummary(tmpObj), min(0.), max(1.), numtracks(10), goodTrackMask(1 << 2) {};
		
			void setPointer(KDataTracks * tmpObj);
			void setPointer(KTrackSummary * tmpObj);
		
			void setGoodTrackMask(unsigned int tmp_);
			void setNumTracks(int numtracks_);
			void setMinCut(double min_);
			void setMaxCut(double max_);
		
			virtual bool getInternalDecision();
			double getDecisionValue();
	};
}
#endif
