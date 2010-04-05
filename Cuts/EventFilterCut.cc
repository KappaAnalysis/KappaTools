#include "EventFilterCut.h"

namespace KappaTools
{
	RunLumiEvtBXRange::RunLumiEvtBXRange(unsigned long nRun_, unsigned long nLumiMin_ = 0, unsigned long nLumiMax_ = 0, unsigned long nBX_ = 0) :
		nRun(nRun_),
		nLumiMin(nLumiMin_),
		nLumiMax(nLumiMax_),
		nBX(nBX_)
		{};
	bool RunLumiEvtBXRange::contains(KEventMetadata * evt)
	{
		//std::cout << evt->nRun << "\t" << nRun << "\n";

		if (evt->nRun != nRun)
			return false;
		if (evt->nBX != nBX)
			return false;

		if (nLumiMin==0 && nLumiMax == 0)
			return true;

		if (nLumiMin==0 && evt->nLumi<=nLumiMax)
			return true;

		if (nLumiMin<=evt->nLumi && nLumiMax == 0)
			return true;

		if (nLumiMin<=evt->nLumi && evt->nLumi<=nLumiMax)
			return true;

		return false;
	}



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

		//std::cout << whitelist.size() << "\n";
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

