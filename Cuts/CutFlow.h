#ifndef KCutFlow_h
#define KCutFlow_h

#include <vector>
#include <algorithm>

#include "BaseCut.h"
#include <iostream>
#include <iomanip>
#include <boost/dynamic_bitset.hpp>
#include "TH1F.h"

namespace KappaTools
{
	class CutFlow
	{
	private:
		std::vector< KappaTools::BaseCut * > cutFlow;
	public:
		void addCut(KappaTools::BaseCut * cut);
		void addCut(CutFlow * cf);
		size_t size();

		std::string getCutName(size_t i);
		void printCutList();
		void printDecisionValues();

		boost::dynamic_bitset<> getDecisionVector();
		std::vector< double > getCutValues();
		std::vector< double > getDecisionValues();
		boost::dynamic_bitset<> getAccDecisionVector();	// vector is 1 until the first decision is false

		bool successful();
		unsigned int getAccSuccessfulCuts();

		bool allMinusOneSuccessful(KappaTools::BaseCut * cut);
		bool allMinusTwoSuccessful(KappaTools::BaseCut * cut1, KappaTools::BaseCut * cut2);
		bool allMinusOneSuccessful(size_t cut);
		bool allMinusTwoSuccessful(size_t cut1, size_t cut2);
		bool allBeforeSuccessful(KappaTools::BaseCut * cut);

		const std::vector< KappaTools::BaseCut * > getCutFlow();
		virtual void initEvaluation(bool autoPrefix = false);
		void evaluate();

		CutFlow();
		CutFlow(CutFlow * cf);
	};

	class CutflowTable
	{
	private:
		CutFlow * cutflow;
		boost::dynamic_bitset<> tmpResult;
		std::vector<unsigned long> cutflowTable;
	public:
		CutflowTable();
		CutflowTable(CutFlow * cutflow_);
		void collect(KappaTools::BaseCut * cut = 0);
		void nextEvent();
		void printTable();
		void writeHistogram(std::string histoname);
		unsigned long get(size_t idx);
		size_t size();
	};
}
#endif
