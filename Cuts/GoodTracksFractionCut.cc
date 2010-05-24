#include "GoodTracksFractionCut.h"

namespace KappaTools
{
	void GoodTracksFractionCut::setPointer(KDataTracks * tmpObj)
	{
		obj_Tracks=tmpObj;
		obj_TrackSummary=0;
	}

	void GoodTracksFractionCut::setPointer(KTrackSummary * tmpObj)
	{
		obj_Tracks=0;
		obj_TrackSummary=tmpObj;
	}

	void GoodTracksFractionCut::setGoodTrackMask(unsigned int tmp_)
	{
		goodTrackMask = tmp_;
	}

	void GoodTracksFractionCut::setNumTracks(int numtracks_)
	{
		numtracks=numtracks_;
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
		if (!obj_Tracks && !obj_TrackSummary)
			return false;

		if (obj_TrackSummary && obj_TrackSummary->nTracks <= numtracks)
			return true;
		if (obj_Tracks && obj_Tracks->size() <= numtracks)
			return true;

		double val = getDecisionValue();
	
		return (val>min && val<max);
	};

	double GoodTracksFractionCut::getDecisionValue()
	{
		if (!obj_Tracks && !obj_TrackSummary)
			return -1.;

		if (obj_TrackSummary)
		{
			return (double)obj_TrackSummary->nTracksHQ / (double)obj_TrackSummary->nTracks;
		}
		else
		{
			double goodTracks = 0;
			double allTracks = obj_Tracks->size();

			for (KDataTracks::iterator it = obj_Tracks->begin(); it != obj_Tracks->end(); it++)
				if (it->quality & goodTrackMask)
					goodTracks++;

			return goodTracks/allTracks;
		}
	};
}
