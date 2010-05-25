#ifndef KTrackChi2Cut_h
#define KTrackChi2Cut_h

#include "TMath.h"
#include "BaseCut.h"
#include "DataFormats/interface/KBasic.h"
#include "DataFormats/interface/KTrack.h"

namespace KappaTools
{
	template <typename T>
	class TrackChi2Cut : public BaseCut
	{
		private:
			T * obj;
			short min, max;
			unsigned char type;
		public:
			enum Type
			{
				CHI2,
				NDOF,
				CHI2NORM,
				CHI2PROB
			};

			TrackChi2Cut();
			TrackChi2Cut(T * tmpObj);

			void setPointer(T * tmpObj);

			void setType(unsigned char type_);
			void setMinCut(unsigned short min_);
			void setMaxCut(unsigned short max_);

			virtual bool getInternalDecision();
			double getDecisionValue();
	};
}

#endif
