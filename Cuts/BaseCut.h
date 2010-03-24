#ifndef KBaseCut_h
#define KBaseCut_h

#include <string>
#include <iostream>
#include "TNtuple.h"

namespace KappaTools
{
	class BaseCut
	{
		protected:
			std::string cutName;
			TNtuple * eval_tuple;
		public:
			BaseCut(std::string tmpCutName);
			bool getDecision();
			virtual bool getInternalDecision() = 0;
			virtual double getDecisionValue() = 0;
			//virtual std::string setName(std::string tmpName) = 0;
			virtual void setName(std::string tmpCutName);
			virtual std::string getName();
			virtual void initEvaluation(std::string name = "");
			virtual void evaluate();
	};

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
#endif
