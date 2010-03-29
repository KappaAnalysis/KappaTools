#include "GoodTracksFractionCut.h"

namespace KappaTools
{
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
