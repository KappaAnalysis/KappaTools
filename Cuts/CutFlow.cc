#include "CutFlow.h"

namespace KappaTools
{
	CutFlow::CutFlow()
	{
		cutFlow.clear();
	}
	CutFlow::CutFlow(CutFlow * cf)
	{
		cutFlow.clear();
		std::vector< BaseCut * > tmp = cf->getCutFlow();
		for (std::vector< BaseCut * >::const_iterator it = tmp.begin(); it != tmp.end(); it++)
		{
			cutFlow.push_back((*it));
		}
	}
	void CutFlow::addCut(KappaTools::BaseCut * cut)
	{
		cutFlow.push_back(cut);
	}
	void CutFlow::addCut(CutFlow * cf)
	{
		std::vector< BaseCut * > tmp = cf->getCutFlow();
		for (std::vector< BaseCut * >::const_iterator it = tmp.begin(); it != tmp.end(); it++)
			cutFlow.push_back((*it));
	}
	std::string CutFlow::getCutName(size_t i)
	{
		return (i < cutFlow.size() ? cutFlow[i]->getName() : "-");
	}
	void CutFlow::printCutList()
	{
		int i = 1;
		for (std::vector< BaseCut * >::iterator it = cutFlow.begin(); it != cutFlow.end(); it++)
		{
			std::cout << (i++) << ".: " << (*it)->getName() << std::endl;
		}
	}
	// evaluates all but one cut
	bool CutFlow::allMinusOneSuccessful(size_t cut)
	{
		return allMinusOneSuccessful(cutFlow.at(cut));
	}
	// evaluates all but two cuts
	bool CutFlow::allMinusTwoSuccessful(size_t cut1, size_t cut2)
	{
		return allMinusTwoSuccessful(cutFlow.at(cut1), cutFlow.at(cut2));
	}
	// evaluates all but one cut
	bool CutFlow::allMinusOneSuccessful(KappaTools::BaseCut * cut)
	{
		for (std::vector< BaseCut * >::iterator it = cutFlow.begin(); it != cutFlow.end(); it++)
			if (cut != (*it) && !((*it)->getDecision()))
				return false;
		return true;
	}
	// evaluates all but two cuts
	bool CutFlow::allMinusTwoSuccessful(KappaTools::BaseCut * cut1, KappaTools::BaseCut * cut2)
	{
		for (std::vector< BaseCut * >::iterator it = cutFlow.begin(); it != cutFlow.end(); it++)
			if (cut1 != (*it) && cut2 != (*it) && !((*it)->getDecision()))
				return false;
		return true;
	}
	bool CutFlow::allBeforeSuccessful(KappaTools::BaseCut * cut)
	{
		for (std::vector< BaseCut * >::iterator it = cutFlow.begin(); it != cutFlow.end(); it++)
			if ( cut==(*it))
				return true;
			else
				if (!((*it)->getDecision()))
					return false;
		return false;
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
	size_t CutFlow::size()
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
			std::cout << "value of " << (*it)->getName() << ": \t" << (*it)->getDecisionValue() << "\t" << ((*it)->getDecision() ? "+" : "-") << std::endl;
		std::cout << std::endl;
	}
	boost::dynamic_bitset<> CutFlow::getAccDecisionVector()
	{
		// vector is 1 until the first decision is false
		boost::dynamic_bitset<> dec(cutFlow.size());
		for (size_t idx = 0; idx < cutFlow.size(); ++idx)
			if (cutFlow[idx]->getDecision())
				dec[idx] = true;
			else
				break;
		return dec;
	}
	unsigned int CutFlow::getSuccessfulCuts() const
	{
		unsigned int c = 0;
		for (size_t idx = 0; idx < cutFlow.size(); ++idx)
			if (cutFlow[idx]->getDecision())
				++c;
		return c;
	}
	unsigned int CutFlow::getAccSuccessfulCuts()
	{
		// vector is 1 until the first decision is false
		for (size_t idx = 0; idx < cutFlow.size(); ++idx)
			if (!cutFlow[idx]->getDecision())
				return (unsigned int)idx;
		return (unsigned int)cutFlow.size();
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
	const std::vector< KappaTools::BaseCut * > KappaTools::CutFlow::getCutFlow()
	{
		return cutFlow;
	}

	KappaTools::CutflowTable::CutflowTable()
	{
		cutflow = 0;
	}

	KappaTools::CutflowTable::CutflowTable(CutFlow * cutflow_)
	{
		cutflow = cutflow_;

		tmpResult = cutflow->getAccDecisionVector();
		for (size_t idx = 0; idx < cutflow->size(); idx++)
			tmpResult[idx] = 0;
		tmpResult[0] = 1;

		cutflowTable = std::vector<unsigned long>(cutflow->size());
	}

	// collect all cuts up to a specified cut (inclusive)
	// with this one can use an event based selection and a combinatorial
	// selection of objects in one cut flow
	void KappaTools::CutflowTable::collect(KappaTools::BaseCut * cut)
	{
		if (!cutflow)
			return;

		boost::dynamic_bitset<> tempCollect = cutflow->getAccDecisionVector();

		for (size_t idx = 0; idx < cutflow->size(); idx++)
		{
			tmpResult[idx] |= tempCollect[idx];
			if (cutflow->getCutFlow().at(idx) == cut)
				break;
		}
	}

	void KappaTools::CutflowTable::nextEvent()
	{
		if (!cutflow)
			return;

		for (size_t idx = 0; idx < cutflow->size(); idx++)
		{
			cutflowTable[idx] += tmpResult[idx];
			tmpResult[idx] = 0;
		}
		tmpResult[0] = 1;
	}

	void KappaTools::CutflowTable::printTable()
	{
		if (!cutflow)
			return;

		for (size_t idx = 0; idx < cutflow->size(); idx++)
		{
			std::string tmpName = cutflow->getCutName(idx);
			std::cout << idx << ".:\t" << tmpName << "";
			for (size_t i = 0; i < std::max<unsigned long>(0, 40 - tmpName.length()); i++)
				std::cout << " ";
			std::cout << cutflowTable[idx] << "\t";
			std::cout << std::setprecision(4) <<   cutflowTable[idx] / (double)cutflowTable[0] << "\t";
			std::cout << std::setprecision(4) << (idx > 0 ? (cutflowTable[idx] / (double)cutflowTable[idx-1]) : 1.) << std::endl;
		}
		std::cout << std::endl;
	}

	void KappaTools::CutflowTable::writeHistogram(std::string histoname)
	{
		TH1F * histo = new TH1F(histoname.c_str(), histoname.c_str(), cutflow->size(), 0, cutflow->size());
		for (size_t idx = 0; idx < cutflow->size(); idx++)
		{
			histo->SetBinContent(idx + 1, cutflowTable[idx]);
			histo->GetXaxis()->SetBinLabel(idx + 1, cutflow->getCutName(idx).c_str());
		}
		histo->Write();
	}

	unsigned long KappaTools::CutflowTable::get(size_t idx)
	{
		return cutflowTable.at(idx);
	}

	size_t KappaTools::CutflowTable::size()
	{
		return cutflowTable.size();
	}
}
