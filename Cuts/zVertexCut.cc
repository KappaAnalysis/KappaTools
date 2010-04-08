#include "zVertexCut.h"

namespace KappaTools
{
	zVertexCut::zVertexCut()	: BaseCut("z vtx cut"), obj(0), min(0.), max(1e6) {}
	
	zVertexCut::zVertexCut(KDataVertex * tmpObj) : BaseCut("z vtx cut"), obj(tmpObj), min(0.), max(1e6) {}

	void zVertexCut::setPointer(KDataVertex * tmpObj)
	{
		obj = tmpObj;
	}
	
	void zVertexCut::setMinCut(double min_)
	{
		min = min_;
	}
	
	void zVertexCut::setMaxCut(double max_)
	{
		max = max_;
	}

	bool zVertexCut::getInternalDecision()
	{
		if (!obj)
			return false;
		
		double val = getDecisionValue();
		return (val>min && val<max);
	};

	double zVertexCut::getDecisionValue()
	{
		if (!obj)
			return -1.;
		else
			return obj->position.z();
	};
}
