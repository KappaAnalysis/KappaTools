#include "CutGroup.h"

namespace KappaTools
{
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
