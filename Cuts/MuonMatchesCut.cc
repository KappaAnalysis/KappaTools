#include "MuonMatchesCut.h"

namespace KappaTools
{

	MuonMatchesCut::MuonMatchesCut()	: BaseCut("nr. of matches"), obj(0), min(0), max(-1) {}


	MuonMatchesCut::MuonMatchesCut(KDataMuon * tmpObj) : BaseCut("nr. of matches"), obj(tmpObj), min(0), max(-1) {}


	void MuonMatchesCut::setPointer(KDataMuon * tmpObj)
	{
		obj = tmpObj;
	}

	void MuonMatchesCut::setMinCut(double min_)
	{
		min = min_;
	}


	void MuonMatchesCut::setMaxCut(double max_)
	{
		max = max_;
	}


	bool MuonMatchesCut::getInternalDecision()
	{
		if (!obj)
			return false;

		double val = getDecisionValue();

		if (max == -1)
			return (val > min);
		else
			return (val > min && val < max);
	}


	double MuonMatchesCut::getDecisionValue()
	{
		if (!obj)
			return -1.;

		return obj->numberOfMatches;
	}
}
