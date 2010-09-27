#include "EventFilterCut.h"
#include <algorithm>

namespace KappaTools
{
	RunLumiEvtBXRange::RunLumiEvtBXRange(run_id nRun_, lumi_id nLumiMin_, lumi_id nLumiMax_, bx_id nBX_) :
			nRun(nRun_),
			nLumiMin(nLumiMin_),
			nLumiMax(nLumiMax_),
			nBX(nBX_)
	{};
	bool RunLumiEvtBXRange::contains(KEventMetadata * evt)
	{
		if (evt->nRun != nRun)
			return false;
		if (nBX != 0 && evt->nBX != nBX)
			return false;

		if (nLumiMin == 0 && nLumiMax == 0)
			return true;

		if (nLumiMin == 0 && evt->nLumi <= nLumiMax)
			return true;

		if (nLumiMin <= evt->nLumi && nLumiMax == 0)
			return true;

		if (nLumiMin <= evt->nLumi && evt->nLumi <= nLumiMax)
			return true;

		return false;
	}
	unsigned long RunLumiEvtBXRange::getRun()
	{
		return nRun;
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
		obj = tmpObj;
	}

	void EventFilterCut::addRange(std::vector<RunLumiEvtBXRange> range_)
	{
		for (std::vector<RunLumiEvtBXRange>::iterator it = range_.begin(); it != range_.end(); ++it)
			whitelist.push_back(*it);
	}
	void EventFilterCut::addRange(RunLumiEvtBXRange range_)
	{
		whitelist.push_back(range_);
	}

	void EventFilterCut::clearList()
	{
		whitelist.clear();
	}

	std::vector<unsigned long> EventFilterCut::getRuns()
	{
		std::vector<unsigned long> usedRuns;
		for (std::vector<RunLumiEvtBXRange>::iterator it = whitelist.begin(); it != whitelist.end(); ++it)
			if (find(usedRuns.begin(), usedRuns.end(), it->getRun()) == usedRuns.end())
				usedRuns.push_back(it->getRun());

		stable_sort(usedRuns.begin(), usedRuns.end());
		return usedRuns;
	}

	bool EventFilterCut::getInternalDecision()
	{
		if (!obj)
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
