#include "HLTriggerCut.h"

namespace KappaTools
{
	HLTriggerCut::HLTriggerCut() :
			BaseCut("HLT cut"),
			obj(0),
			min(-1),
			max(-1)
	{}

	HLTriggerCut::HLTriggerCut(KEventMetadata * tempObj) :
			BaseCut("HLT cut"),
			obj(tempObj),
			min(-1),
			max(-1)
	{}

	HLTriggerCut::HLTriggerCut(KEventMetadata * tempObj, std::vector<std::string> selected_) :
			BaseCut("HLT cut"),
			obj(tempObj),
			selected(selected_),
			min(selected_.size()),
			max(selected_.size())
	{}

	HLTriggerCut::HLTriggerCut(std::vector<std::string> selected_) :
			BaseCut("HLT cut"),
			selected(selected_),
			min(selected_.size()),
			max(selected_.size())
	{}

	HLTriggerCut::HLTriggerCut(KEventMetadata * tempObj, std::vector<std::string> selected_, int min_) :
			BaseCut("HLT cut"),
			obj(tempObj),
			selected(selected_),
			min(min),
			max(-1)
	{}

	HLTriggerCut::HLTriggerCut(KEventMetadata * tempObj, std::vector<std::string> selected_, int min_, int max_) :
			BaseCut("HLT cut"),
			obj(tempObj),
			selected(selected_),
			min(min_),
			max(max_)
	{}

	void HLTriggerCut::setTriggerMap(KLumiMetadata * tmpLumiMetadata)
	{
		std::map<std::string, int> tmpHltNamesMap;

		int idx = 0;
		for (std::vector<std::string>::iterator it = tmpLumiMetadata->hltNames.begin(); it != tmpLumiMetadata->hltNames.end(); it++)
		{
			std::string tmpName = *it;

			if (tmpHltNamesMap[tmpName])
				continue;

			tmpHltNamesMap[tmpName] = idx++;
		}
		hltMap = tmpHltNamesMap;
	}

	void HLTriggerCut::setTrigger(std::vector<std::string> selected_)
	{
		selected = selected_;
		min = selected_.size();
		max = selected_.size();
	}

	void HLTriggerCut::setTrigger(std::string selected_)
	{
		selected.clear();
		selected.push_back(selected_);
		min = 1;
		max = 1;
	}

	void HLTriggerCut::setPointer(KEventMetadata * tmpObj)
	{
		obj = tmpObj;
	}

	void HLTriggerCut::setCut(int min_)
	{
		min = min_;
	}

	void HLTriggerCut::setCut(int min_, int max_)
	{
		min = min_;
		max = max_;
	}

	void HLTriggerCut::setMinCut(int min_)
	{
		min = min_;
	}

	void HLTriggerCut::setMaxCut(int max_)
	{
		max = max_;
	}

	bool HLTriggerCut::isTriggerAvailable()
	{
		for (std::vector<std::string>::iterator it = selected.begin(); it != selected.end() ; it++)
			if (hltMap.find(*it) == hltMap.end())
				return false;
		return true;
	}

	bool HLTriggerCut::getInternalDecision()
	{
		if (!obj)
			return false;

		int fired = 0;
		for (std::vector<std::string>::iterator it = selected.begin(); it != selected.end() ; it++)
		{
			if (hltMap.find(*it) == hltMap.end())
				continue;

			if ((obj->bitsHLT & ((unsigned long long)1 << hltMap[*it])) != 0)
				fired++;
		}
		firedTriggers = fired;
		return (fired >= min && fired <= max) || (max == -1 && fired >= min);
	}

	double HLTriggerCut::getDecisionValue()
	{
		getInternalDecision();
		return firedTriggers;
	}
}
