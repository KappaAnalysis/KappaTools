#ifndef KTrackQualityCut_h
#define KTrackQualityCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KBasic.h"

namespace KappaTools
{
	template <typename T>
	class TrackQualityCut : public BaseCut
	{
		private:
			T * obj;
			int mask;
		public:
			enum TrackQuality { undefQuality=-1, loose=0, tight=1, highPurity=2, confirmed=3, goodIterative=4, qualitySize=5};

			TrackQualityCut();
			TrackQualityCut(T * tmpObj);

			void setPointer(T * tmpObj);

			void setCut(int mask_);
			
			virtual bool getInternalDecision();
			double getDecisionValue();
	};
}
#endif
