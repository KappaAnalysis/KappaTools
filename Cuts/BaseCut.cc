#include "BaseCut.h"
namespace KappaTools
{
	BaseCut::BaseCut(std::string tmpCutName) : cutName(tmpCutName), mode(NORMAL), eval_tuple(0) {}

	bool BaseCut::getDecision()
	{
		switch (mode)
		{
			case ALWAYSTRUE:
				return true;
			case ALWAYSFALSE:
				return false;
			case INVERTED:
				return !getInternalDecision();
			default:
				return getInternalDecision();
		}
	}

	void BaseCut::setDecisionMode(char mode_)
	{
		mode = mode_;
	}

	void BaseCut::setName(std::string tmpCutName)
	{
		cutName = tmpCutName;
		if (eval_tuple)
			eval_tuple->SetName((TString)tmpCutName);
	}

	std::string BaseCut::getName()
	{
		return cutName;
	}

	void BaseCut::initEvaluation(std::string name)
	{
		if (name == "")
			name = cutName;
		eval_tuple = new TNtuple(((TString)"eval_" + name).ReplaceAll(" ", "_").ReplaceAll(".", "").ReplaceAll("<", "").ReplaceAll(">", "").ReplaceAll(":", "").ReplaceAll(",", ""), (TString)name, "value:decision");
	}

	void BaseCut::evaluate()
	{
		if (eval_tuple)
			eval_tuple->Fill(getDecisionValue(), getDecision());
	}
}
