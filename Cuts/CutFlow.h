#ifndef KCutFlow_h
#define KCutFlow_h

#include <vector>
#include "BaseCut.h"
#include <iostream>
#include <boost/dynamic_bitset.hpp>

namespace KappaTools
{
	class CutFlow
	{	
		private:
			std::vector< KappaTools::BaseCut * > cutFlow;
		public:
			void addCut(KappaTools::BaseCut * cut);
			unsigned int size();
			
			std::string getCutName(unsigned int i);
			void printCutList();
			void printDecisionValues();
			
			boost::dynamic_bitset<> getDecisionVector();
			std::vector< double > getCutValues();
			std::vector< double > getDecisionValues();
			boost::dynamic_bitset<> getAccDecisionVector();	// vector is 1 until the first decision is false

			bool successful();		
			unsigned int getAccSuccessfulCuts();

			bool allMinusOneSuccessful(KappaTools::BaseCut * cut);
			bool allMinusTwoSuccessful(KappaTools::BaseCut * cut1, KappaTools::BaseCut * cut2);
			bool allMinusOneSuccessful(unsigned int cut);
			bool allMinusTwoSuccessful(unsigned int cut1, unsigned int cut2);
			
			void initEvaluation(bool autoPrefix = false);
			void evaluate();
	};
}
#endif
