#ifndef KTrackHitsCut_h
#define KTrackHitsCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KTrack.h"

namespace KappaTools
{
	template <typename T>
	class TrackHitsCut : public BaseCut
	{
	private:
		T * obj;
		short min, max;
		int type;
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
			nLostHits,
			nTrackerHits // composition
		};

		TrackHitsCut();
		TrackHitsCut(T * tmpObj);
		TrackHitsCut(int type_);

		void setPointer(T * tmpObj);

		void setType(int type_);
		void setMinCut(unsigned short min_);
		void setMaxCut(unsigned short max_);

		virtual bool getInternalDecision();
		double getDecisionValue();
	};
}
#endif
