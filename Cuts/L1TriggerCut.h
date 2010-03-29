#ifndef KL1TriggerCut_h
#define KL1TriggerCut_h

#include "BaseCut.h"
#include <stdlib.h>
#include <stack>
#include "DataFormats/interface/KMetadata.h"

namespace KappaTools
{
	/*
		explanation:
			This cut can evaluate the Level 1 trigger with arbitrary
			term containing boolean algebra. To achieve this flexibility,
			it uses a post-fix notation, i.e.
				(3 & 2) | !1 --> 3 2 & 1 ! |
			see: http://en.wikipedia.org/wiki/Reverse_Polish_notation
	*/
	class L1TriggerCut : public BaseCut
	{
		private:
			unsigned long long * l1;
			std::vector<int> commands;
			bool debug;
		public:
			static const int NOT = -1;
			static const int AND = -2;
			static const int OR  = -3;
			static const int XOR = -4;

			L1TriggerCut();
			void setPointer(unsigned long long * tmpObj);
			void setPointer(KEventMetadata * tmpObj);
			void addCommand(int cmd);
			void clearCommands();
			void testBit(int cmd);
			void setDebug(bool debug_);

			virtual bool getInternalDecision();

			double getDecisionValue();
	};
}
#endif
