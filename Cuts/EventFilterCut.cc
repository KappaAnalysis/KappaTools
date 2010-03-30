#include "EventFilterCut.h"

namespace KappaTools
{
	EventFilterCut::EventFilterCut() :
		BaseCut("evt. filter"),
		obj(0)
		{}

	EventFilterCut::EventFilterCut(KEventMetadata * tempObj) :
		BaseCut("evt. filter"),
		obj(tempObj)
		{}

	void EventFilterCut::setPointer(KEventMetadata * tmpObj)
	{
		obj=tmpObj;
	}

	void EventFilterCut::addRange(RunLumiEvtBXRange range_)
	{
		whitelist.push_back(range_);
	}

	void EventFilterCut::clearList()
	{
		whitelist.clear();
	}

	bool EventFilterCut::getInternalDecision()
	{
		if(!obj)
			return false;

		for (std::vector<RunLumiEvtBXRange>::iterator it = whitelist.begin(); it != whitelist.end(); ++it)
			if (it->contains(obj))
				return true;

		return false;
	}

	double EventFilterCut::getDecisionValue()
	{
		return getInternalDecision();
	}
}

