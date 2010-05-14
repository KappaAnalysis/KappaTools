#ifndef KTrackHitsCut_h
#define KTrackHitsCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KBasic.h"

namespace KappaTools
{
	template <typename T>
	class TrackHitsCut : public BaseCut
	{
		private:
			T * obj;
			unsigned char type;
			unsigned short min, max;
		public:
			enum TrackHitsType
			{
				nPixelLayers,
				nStripLayers,
				nValidPixelHits,
				nValidStripHits,
				nValidMuonHits,
				nLostMuonHits,
				nBadMuonHits,
				nValidHits,
				nLostHits
			};

			TrackHitsCut();
			TrackHitsCut(T * tmpObj);

			void setPointer(T * tmpObj);

			void setType(unsigned char type_);
			void setMinCut(unsigned short min_);
			void setMaxCut(unsigned short max_);
			
			virtual bool getInternalDecision();
			double getDecisionValue();
	};
}
#endif
