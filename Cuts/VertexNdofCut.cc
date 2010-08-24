#include "VertexNdofCut.h"

namespace KappaTools
{
	void VertexNdofCut::setPointer(KDataVertex * tmpObj)
	{
		obj = tmpObj;
	}

	void VertexNdofCut::setMinCut(int min_)
	{
		min = min_;
	}

	void VertexNdofCut::setMaxCut(int max_)
	{
		max = max_;
	}

	bool VertexNdofCut::getInternalDecision()
	{
		if (!obj)
			return false;

		double val = getDecisionValue();

		if (max == -1)
			if (val > min)
				return true;
			else
				return false;
		else
			return (val > min && val < max);
	};

	double VertexNdofCut::getDecisionValue()
	{
		if (!obj)
			return -1.;

		return obj->nDOF;
	};
}
