#include "L1TriggerCut.h"

namespace KappaTools
{
	L1TriggerCut::L1TriggerCut() : BaseCut("L1 cut"), l1(0), debug(false)
	{
		commands.clear();
	}

	void L1TriggerCut::setPointer(unsigned long long * tmpObj)
	{
		l1 = tmpObj;
	}

	void L1TriggerCut::setPointer(KEventMetadata * tmpObj)
	{
		l1 = &(tmpObj->bitsL1);
	}

	void L1TriggerCut::clearCommands()
	{
		commands.clear();
	}

	void L1TriggerCut::testBit(int cmd)
	{
		commands.clear();
		commands.push_back(cmd);
	}

	void L1TriggerCut::addCommand(int cmd)
	{
		commands.push_back(cmd);
	}

	void L1TriggerCut::setDebug(bool debug_)
	{
		debug = debug_;
	}

	bool L1TriggerCut::getInternalDecision()
	{
		if (!l1)
			return false;

		std::stack<bool> calc;
		for (std::vector<int>::iterator it = commands.begin(); it != commands.end(); it++)
		{
			int cmd = (*it);
			if (debug)
				std::cout << "elements on stack: " << calc.size() << "\tnext command: " << cmd << "\n";
			if (cmd>=0)
				calc.push( (*l1 & ((unsigned long long)1 << cmd)) );
			if (cmd == L1TriggerCut::NOT)
			{
				int arg1 = calc.top(); calc.pop();
				calc.push(!arg1);
			}
			if (cmd == L1TriggerCut::AND)
			{
				int arg1 = calc.top(); calc.pop();
				int arg2 = calc.top(); calc.pop();
				calc.push( arg1 & arg2);
			}
			if (cmd == L1TriggerCut::OR)
			{
				int arg1 = calc.top(); calc.pop();
				int arg2 = calc.top(); calc.pop();
				calc.push( arg1 | arg2);
			}
			if (cmd == L1TriggerCut::XOR)
			{
				int arg1 = calc.top(); calc.pop();
				int arg2 = calc.top(); calc.pop();
				calc.push( arg1 ^ arg2);
			}
		}
		if (calc.size()>1)
			throw("evaluation failed, please check your L1 trigger cut syntax");
		if (calc.size()>0)
			return calc.top();
		else
			return false;
	}

	double L1TriggerCut::getDecisionValue()
	{
		return getInternalDecision();
	}
}
