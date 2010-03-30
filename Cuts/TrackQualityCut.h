#ifndef KTrackQualityCut_h
#define KTrackQualityCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KBasic.h"

// note:
//  TrackQualityBitmask is already a bit mask!!
//  (in contrast to reco::TrackBase::TrackQuality which is only
//   the bit position)
namespace KappaTools
{
	template <typename T>
	class TrackQualityCut : public BaseCut
	{
		private:
			T * obj;
			int mask;
		public:
			enum TrackQualityBitmask {
				loose = 1 << 0,
				tight = 1 << 1,
				highPurity = 1 << 2,
				confirmed = 1 << 3,
				goodIterative = 1 << 4,
				qualitySize = 1 << 5
				};

			TrackQualityCut();
			TrackQualityCut(T * tmpObj);

			void setPointer(T * tmpObj);

			void setCut(int mask_);
			
			virtual bool getInternalDecision();
			double getDecisionValue();
	};
}
#endif
