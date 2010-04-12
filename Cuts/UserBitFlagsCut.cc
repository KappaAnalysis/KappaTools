#include "UserBitFlagsCut.h"

namespace KappaTools
{
	UserBitFlagsCut::UserBitFlagsCut() :
		BaseCut("user bit cut"),
		obj(0),
		min(-1),
		max(-1)
		{}

	UserBitFlagsCut::UserBitFlagsCut(KEventMetadata * tempObj) :
		BaseCut("user bit cut"),
		obj(tempObj),
		min(-1),
		max(-1)
		{}

	UserBitFlagsCut::UserBitFlagsCut(KEventMetadata * tempObj, std::vector<unsigned long> selected_) :
		BaseCut("user bit cut"),
		obj(tempObj),
		selected(selected_),
		min(selected_.size()),
		max(selected_.size())
		{}

	UserBitFlagsCut::UserBitFlagsCut(std::vector<unsigned long> selected_) :
		BaseCut("user bit cut"),
		selected(selected_),
		min(selected_.size()),
		max(selected_.size())
		{}

	UserBitFlagsCut::UserBitFlagsCut(KEventMetadata * tempObj, std::vector<unsigned long> selected_, int min_) :
		BaseCut("user bit cut"),
		obj(tempObj),
		selected(selected_),
		min(min),
		max(-1)
		{}

	UserBitFlagsCut::UserBitFlagsCut(KEventMetadata * tempObj, std::vector<unsigned long> selected_, int min_, int max_) :
		BaseCut("user bit cut"),
		obj(tempObj),
		selected(selected_),
		min(min_),
		max(max_)
		{}

	void UserBitFlagsCut::setTrigger(std::vector<unsigned long> selected_)
	{
		selected = selected_;
		min=selected_.size();
		max=selected_.size();
	}

	void UserBitFlagsCut::setPointer(KEventMetadata * tmpObj)
	{
		obj=tmpObj;
	}

	void UserBitFlagsCut::setCut(int min_)
	{
		min = min_;
	}

	void UserBitFlagsCut::setCut(int min_, int max_)
	{
		min = min_;
		max = max_;
	}

	void UserBitFlagsCut::setMinCut(int min_)
	{
		min = min_;
	}

	void UserBitFlagsCut::setMaxCut(int max_)
	{
		max = max_;
	}

	bool UserBitFlagsCut::getInternalDecision()
	{
		if(!obj)
			return false;

		int fired=0;
		for (std::vector<unsigned long>::iterator it = selected.begin(); it != selected.end() ; it++)
		{
			if ( (obj->bitsUserFlags & (*it)) != 0 )
				fired++;
		}
		firedTriggers=fired;
		return (fired>=min && fired<=max) || (max==-1 && fired>=min);
	}

	double UserBitFlagsCut::getDecisionValue()
	{
		getInternalDecision();
		return firedTriggers;
	}
}

