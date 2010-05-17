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
			int mode;
			TNtuple * eval_tuple;
		public:
			static const char NORMAL = 1;
			static const char ALWAYSTRUE = 2;
			static const char ALWAYSFALSE = 3;
			static const char INVERTED = 4;

			BaseCut(std::string tmpCutName);
			virtual ~BaseCut() {};
			bool getDecision();
			void setDecisionMode(char mode_);
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
