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
}
#endif
