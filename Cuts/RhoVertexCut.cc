#include "RhoVertexCut.h"

namespace KappaTools
{
	RhoVertexCut::RhoVertexCut()	: BaseCut("rho vtx cut"), obj(0), min(0.), max(1e6) {}

	RhoVertexCut::RhoVertexCut(KDataVertex * tmpObj) : BaseCut("rho vtx cut"), obj(tmpObj), min(0.), max(1e6) {}

	void RhoVertexCut::setPointer(KDataVertex * tmpObj)
	{
		obj = tmpObj;
	}

	void RhoVertexCut::setMinCut(double min_)
	{
		min = min_;
	}

	void RhoVertexCut::setMaxCut(double max_)
	{
		max = max_;
	}

	bool RhoVertexCut::getInternalDecision()
	{
		if (!obj)
			return false;

		double val = getDecisionValue();
		return (val > min && val < max);
	};

	double RhoVertexCut::getDecisionValue()
	{
		if (!obj)
			return -1.;
		else
			return obj->position.rho();
	};
}
