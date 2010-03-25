#ifndef KL1TriggerCut_h
#define KL1TriggerCut_h

#include "BaseCut.h"
#include <stdlib.h>
#include <stack>

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
			long long * l1;
			std::vector<int> commands;
		public:
			static const int NOT = -1;
			static const int AND = -2;
			static const int OR	 = -3;
			static const int XOR = -4;
				
			L1TriggerCut();
			void setPointer(long long * tmpObj);
			void addCommand(int cmd);
			void clearCommands();
			void testBit(int cmd);
			
			virtual bool getInternalDecision();		
			
			double getDecisionValue();
	};

	L1TriggerCut::L1TriggerCut() : BaseCut("L1 cut"), l1(0)
	{
		commands.clear();
	}

	void L1TriggerCut::setPointer(long long * tmpObj)
	{
		l1 = tmpObj;
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

	bool L1TriggerCut::getInternalDecision()
	{
		return (getDecisionValue() == 1);
	}	

	double L1TriggerCut::getDecisionValue()
	{
	
		if (!l1)
			return -1;
	
		std::stack<bool> calc;
		for (std::vector<int>::iterator it = commands.begin(); it != commands.end(); it++)
		{
			int cmd = (*it);
			//std::cout << cmd << " " << calc.size() << "  push\n";
			if (cmd>=0)
				calc.push( (*l1 & ((long long)1 << cmd)) );
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
			return 0.;
	}
}
#endif
