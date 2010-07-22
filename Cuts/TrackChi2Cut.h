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
			float min, max;
			int type;
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
			TrackChi2Cut(int type_);

			void setPointer(T * tmpObj);

			void setType(int type_);
			void setMinCut(float min_);
			void setMaxCut(float max_);

			virtual bool getInternalDecision();
			double getDecisionValue();
	};
}

#endif
