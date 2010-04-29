#ifndef KCutGroup_h
#define KCutGroup_h

#include "BaseCut.h"
#include <vector>
namespace KappaTools
{
	class CutGroup : public BaseCut
	{
		private:
			std::vector< KappaTools::BaseCut * > cuts;
			int mode;
		public:
			// available modes:
			static const int AND = 0; // true, if all cuts are passed (default)
			static const int OR  = 1; // true, if at least one cut is passed
			static const int XOR = 2; // true, if only one cut is passed
			static const int NOT = 3; // true, if no cut is passed
			static const int TRU = 4; // true, always, ever, really ever

			CutGroup();
			CutGroup(int mode_);

			void addCut(KappaTools::BaseCut * cut);
			void setMode(int mode_);

			virtual bool getInternalDecision();
			double getDecisionValue();
			void printCutList();
	};
}
#endif
