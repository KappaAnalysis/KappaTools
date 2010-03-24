#include "CutFlow.h"

namespace KappaTools
{
	void CutFlow::addCut(KappaTools::BaseCut * cut)
	{
		cutFlow.push_back(cut);
	}
	std::string CutFlow::getCutName(unsigned int i)
	{
		return ( i<cutFlow.size() ? cutFlow[i]->getName() : "-");
	}
	void CutFlow::printCutList()
	{
		int i=1;
		for (std::vector< BaseCut * >::iterator it = cutFlow.begin(); it != cutFlow.end(); it++)
		{
			std::cout << (i++) <<".: " << (*it)->getName() << "\n";
		}
	}
	// evaluates all but one cut
	bool CutFlow::allMinusOneSuccessful(unsigned int cut)
	{
		return allMinusOneSuccessful(cutFlow.at(cut));
	}
	// evaluates all but two cuts
	bool CutFlow::allMinusTwoSuccessful(unsigned int cut1, unsigned int cut2)
	{
		return allMinusTwoSuccessful(cutFlow.at(cut1),cutFlow.at(cut2));
	}
	// evaluates all but one cut
	bool CutFlow::allMinusOneSuccessful(KappaTools::BaseCut * cut)
	{
		for (std::vector< BaseCut * >::iterator it = cutFlow.begin(); it != cutFlow.end(); it++)
			if ( cut!=(*it) && !((*it)->getDecision()))
				return false;
		return true;
	}
	// evaluates all but two cuts
	bool CutFlow::allMinusTwoSuccessful(KappaTools::BaseCut * cut1, KappaTools::BaseCut * cut2)
	{
		for (std::vector< BaseCut * >::iterator it = cutFlow.begin(); it != cutFlow.end(); it++)
			if ( cut1!=(*it) && cut2!=(*it) && !((*it)->getDecision()))
				return false;
		return true;
	}
	std::vector< double > CutFlow::getCutValues()
	{
		std::vector< double > dec;
		for (std::vector< BaseCut * >::iterator it = cutFlow.begin(); it != cutFlow.end(); it++)
		{
			dec.push_back(((*it)->getDecision() ? 1. : 0.));
		}
		return dec;
	}
	boost::dynamic_bitset<> CutFlow::getDecisionVector()
	{
		boost::dynamic_bitset<> dec(0);
		for (std::vector< BaseCut * >::iterator it = cutFlow.begin(); it != cutFlow.end(); it++)
		{
			dec.push_back((*it)->getDecision());
		}
		return dec;
	}
	std::vector< double > CutFlow::getDecisionValues()
	{
		std::vector<double> val;
		for (std::vector< BaseCut * >::iterator it = cutFlow.begin(); it != cutFlow.end(); it++)
		{
			val.push_back((*it)->getDecisionValue());
		}
		return val;
	}
	unsigned int CutFlow::size()
	{
		return cutFlow.size();
	}
	bool CutFlow::successful()
	{
 		for (std::vector< BaseCut * >::iterator it = cutFlow.begin(); it != cutFlow.end(); it++)
			if (!(*it)->getDecision())
				return false;
		return true;
	}
	void CutFlow::printDecisionValues()
	{
		for (std::vector< BaseCut * >::iterator it = cutFlow.begin(); it != cutFlow.end(); it++)
				std::cout << "value of " << (*it)->getName() << ": \t" << (*it)->getDecisionValue() << "\t" <<((*it)->getDecision()?"+":"-")<< "\n";
		std::cout << "\n";
	}
	boost::dynamic_bitset<> CutFlow::getAccDecisionVector()
	{
		// vector is 1 until the first decision is false
		boost::dynamic_bitset<> dec(cutFlow.size());
		for (unsigned int idx = 0; idx < cutFlow.size(); ++idx)
			if (cutFlow[idx]->getDecision())
				dec[idx]=true;
			else
				break;
		return dec;
	}
	unsigned int CutFlow::getAccSuccessfulCuts()
	{
		// vector is 1 until the first decision is false
		for (unsigned int idx = 0; idx < cutFlow.size(); ++idx)
			if (!cutFlow[idx]->getDecision())
				return idx;
		return cutFlow.size();
	}
	void CutFlow::initEvaluation(bool autoPrefix)
	{
		for (std::vector< BaseCut * >::iterator it = cutFlow.begin(); it != cutFlow.end(); it++)
			(*it)->initEvaluation();
	}
	void CutFlow::evaluate()
	{
		for (std::vector< BaseCut * >::iterator it = cutFlow.begin(); it != cutFlow.end(); it++)
			(*it)->evaluate();
	}
}
