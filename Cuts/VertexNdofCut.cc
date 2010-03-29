#include "VertexNdofCut.h"

namespace KappaTools
{
	void VertexNdofCut::setPointer(KDataVertex * tmpObj)
	{
		obj=tmpObj;
	}

	void VertexNdofCut::setMinCut(double min_)
	{
		min=min_;
	}

	void VertexNdofCut::setMaxCut(double max_)
	{
		max=max_;
	}

	bool VertexNdofCut::getInternalDecision()
	{
		if (!obj)
			return false;
	
		double val = getDecisionValue();
	
		return (val>min && val<max);
	};

	double VertexNdofCut::getDecisionValue()
	{
		if (!obj)
			return -1.;

		return obj->nDOF;
	};
}
