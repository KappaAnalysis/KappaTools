#include "NonFakeVertexCut.h"

namespace KappaTools
{
	NonFakeVertexCut::NonFakeVertexCut()	: BaseCut("fake vtx cut"), obj(0) {}
	
	NonFakeVertexCut::NonFakeVertexCut(KDataVertex * tmpObj) : BaseCut("fake vtx cut"), obj(tmpObj) {}

	void NonFakeVertexCut::setPointer(KDataVertex * tmpObj)
	{
		obj = tmpObj;
	}

	bool NonFakeVertexCut::getInternalDecision()
	{
		if (!obj)
			return false;
		
		return !(obj->fake);
	};

	double NonFakeVertexCut::getDecisionValue()
	{
		return getInternalDecision();
	};
}
