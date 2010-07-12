#ifndef KCutGroup_h
#define KCutGroup_h

#include "BaseCut.h"
#include <vector>
#include <stack>
#include <stdlib.h>

namespace KappaTools
{
	class CutGroup : public BaseCut
	{
		private:
			std::vector< KappaTools::BaseCut * > cuts;
			int mode;
			std::vector<int> commands;
			bool debug;
		public:
			// available modes:
			//	the first four are also available as operators in 'complex' mode!
			static const int NOT = -1; // true, if no cut is passed
			static const int AND = -2; // true, if all cuts are passed (default)
			static const int OR  = -3; // true, if at least one cut is passed
			static const int XOR = -4; // true, if only one cut is passed
			static const int TRU = -5; // true, always, ever, really ever
			static const int COMPLEX = -6; // evaluate an arbitrary expression


			CutGroup();
			CutGroup(int mode_);

			void addCut(KappaTools::BaseCut * cut);
			void clearCuts();
			void setMode(int mode_);

			bool getComplexDecision();
			void addCommand(int cmd);
			void clearCommands();
			void setDebug(bool debug_);

			virtual bool getInternalDecision();
			double getDecisionValue();
			void printCutList();
	};
}
#endif
