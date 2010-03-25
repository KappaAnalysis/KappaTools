#ifndef KGoodTracksFractionCuts_h
#define KGoodTracksFractionCuts_h

#include "BaseCut.h"
#include <vector>
#include "DataFormats/interface/KBasic.h"

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

	void GoodTracksFractionCut::setPointer(KDataTracks * tmpObj)
	{
		obj=tmpObj;
	}

	void GoodTracksFractionCut::setGoodTrackMask(unsigned int tmp_)
	{
		goodTrackMask = tmp_;
	}

	void GoodTracksFractionCut::setMinCut(double min_)
	{
		min=min_;
	}

	void GoodTracksFractionCut::setMaxCut(double max_)
	{
		max=max_;
	}

	bool GoodTracksFractionCut::getInternalDecision()
	{
		if (!obj)
			return false;
	
		double val = getDecisionValue();
	
		return (val>min && val<max);
	};

	double GoodTracksFractionCut::getDecisionValue()
	{
		if (!obj)
			return -1.;

		double goodTracks = 0;
		double allTracks = obj->size();
		for (KDataTracks::iterator it = obj->begin(); it != obj->end(); it++)
		{
			if (it->quality & goodTrackMask)
				goodTracks++;
		}
		return goodTracks/allTracks;
	};
}
#endif
