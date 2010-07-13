#include "CutGroup.h"

namespace KappaTools
{
	CutGroup::CutGroup() : BaseCut("group of cuts"), mode(AND), debug(false) {}

	CutGroup::CutGroup(int mode_) : BaseCut("group of cuts"), mode(mode_), debug(false) {}

	void CutGroup::addCut(KappaTools::BaseCut * cut)
	{
			cuts.push_back(cut);
	}

	void CutGroup::clearCuts()
	{
			cuts.clear();
	}

	void CutGroup::setMode(int mode_)
	{
		mode = mode_;
	}

	bool CutGroup::getInternalDecision()
	{
		if (cuts.size()==0) return false;

		if (mode == COMPLEX)
			return getComplexDecision();

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

	void CutGroup::setDebug(bool debug_)
	{
		debug = debug_;
	}

	void CutGroup::clearCommands()
	{
		commands.clear();
	}

	void CutGroup::addCommand(int cmd)
	{
		commands.push_back(cmd);
	}

	bool CutGroup::getComplexDecision()
	{
		std::stack<bool> calc;
		if (debug)
		{
			for (std::vector< KappaTools::BaseCut * >::iterator it = cuts.begin(); it!=cuts.end(); it++)
				std::cout << (*it)->getDecision();
			std::cout << std::endl;
		}
		for (std::vector<int>::iterator it = commands.begin(); it != commands.end(); it++)
		{
			int cmd = (*it);
			if (debug)
				std::cout << "elements on stack: " << calc.size() << "\tnext command: " << cmd << std::endl;
			if (cmd>=0)
				calc.push( cuts.at((*it))->getDecision() );
			if (cmd == CutGroup::NOT)
			{
				int arg1 = calc.top(); calc.pop();
				calc.push(!arg1);
			}
			if (cmd == CutGroup::AND)
			{
				int arg1 = calc.top(); calc.pop();
				int arg2 = calc.top(); calc.pop();
				calc.push( arg1 & arg2);
			}
			if (cmd == CutGroup::OR)
			{
				int arg1 = calc.top(); calc.pop();
				int arg2 = calc.top(); calc.pop();
				calc.push( arg1 | arg2);
			}
			if (cmd == CutGroup::XOR)
			{
				int arg1 = calc.top(); calc.pop();
				int arg2 = calc.top(); calc.pop();
				calc.push( arg1 ^ arg2);
			}
		}
		if (calc.size()>1)
			throw("evaluation failed, please check your L1 trigger cut syntax");
		if (debug)
			std::cout << "result: " << calc.top() << std::endl;
		if (calc.size()>0)
			return calc.top();
		else
			return false;
	}

	double CutGroup::getDecisionValue()
	{
		return getInternalDecision();
	}

	void CutGroup::printCutList()
	{
		int i=1;
		for (std::vector< BaseCut * >::iterator it = cuts.begin(); it != cuts.end(); it++)
		{
			std::cout << (i++) <<".: " << (*it)->getName() << std::endl;
		}
	}
}
