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
			static const int OR  = 1;	// true, if at least one cut is passed
			static const int XOR = 2;	// true, if only one cut is passed
			static const int NOT = 3;	// true, if no cut is passed
			static const int TRU = 4; // true, always, ever, really ever

			CutGroup();
			CutGroup(int mode_);

			void addCut(KappaTools::BaseCut * cut);
			void setMode(int mode_);

			virtual bool getInternalDecision();
			double getDecisionValue();
			void printCutList();
	};

	CutGroup::CutGroup() : BaseCut("group of cuts"), mode(AND) {}

	CutGroup::CutGroup(int mode_) : BaseCut("group of cuts"), mode(mode_) {}

	void CutGroup::addCut(KappaTools::BaseCut * cut)
	{
			cuts.push_back(cut);
	}

	void CutGroup::setMode(int mode_)
	{
		mode = mode_;
	}

	bool CutGroup::getInternalDecision()
	{
		if (cuts.size()==0) return false;
		unsigned int dec = 0;
		for (std::vector< BaseCut * >::iterator it = cuts.begin(); it != cuts.end(); it++)
			if ((*it)->getDecision())
				dec++;

		if (mode == AND)
			return (dec == cuts.size());
		if (mode == OR)
			return (dec>0);
		if (mode == XOR)
			return (dec==1);
		if (mode == NOT)
			return (dec==0);
		if (mode == TRU)
			return true;
		return false;
	}

	double CutGroup::getDecisionValue()
	{
		return 1.;
	}

	void CutGroup::printCutList()
	{
		int i=1;
		for (std::vector< BaseCut * >::iterator it = cuts.begin(); it != cuts.end(); it++)
		{
			std::cout << (i++) <<".: " << (*it)->getName() << "\n";
		}
	}
}
#endif
