#include "BaseCut.h"
namespace KappaTools
{
	BaseCut::BaseCut(std::string tmpCutName) : cutName(tmpCutName), eval_tuple(0) {}

	bool BaseCut::getDecision()
	{
		return getInternalDecision();
	}

	void BaseCut::setName(std::string tmpCutName)
	{
		cutName=tmpCutName;
		if (eval_tuple)
			eval_tuple->SetName((TString)tmpCutName);
	}

	std::string BaseCut::getName()
	{
		return cutName;
	}

	void BaseCut::initEvaluation(std::string name)
	{
		if (name=="")
			name = cutName;
		eval_tuple = new TNtuple((TString)name, (TString)name, "value:decision");
	}

	void BaseCut::evaluate()
	{
		if (eval_tuple)
			eval_tuple->Fill(getDecisionValue(),getDecision());
	}
}
