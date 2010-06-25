#include "TriggerTest.h"

template <typename JetType, typename METType>
TriggerTest<JetType, METType>::TriggerTest(TDirectory * histofile)
{
	histofile->cd();

	hlTrigger.clear();
	hlTrigger.push_back("HLT_L1Mu");
	hlTrigger.push_back("HLT_Mu3");
	hlTrigger.push_back("HLT_Mu5");
	hlTrigger.push_back("HLT_Mu9");
	hlTrigger.push_back("HLT_DoubleMu3");
	hlTrigger.push_back("HLT_Jet15U");
	hlTrigger.push_back("HLT_Jet30U");
	hlTrigger.push_back("HLT_Jet50U");
	hlTrigger.push_back("HLT_IsoMu3");
	//hlTrigger.push_back("TestPath");

	for (std::vector<std::string>::iterator it = hlTrigger.begin(); it != hlTrigger.end(); it++)
	{
		hltPrescale[*it] = 0;
	}

	histofile->cd();
}

template <typename JetType, typename METType>
void TriggerTest<JetType, METType>::addLog(KEventMetadata * eventMetadata, std::string text)
{
	std::stringstream i_str;
	i_str << "run ";
	i_str << eventMetadata->nRun;
	i_str << "\t ";
	i_str << text;
	problemLog.push_back(i_str.str());
}

template <typename JetType, typename METType>
void TriggerTest<JetType, METType>::processEvent(KEventMetadata * eventMetadata, KLumiMetadata * lumiMetadata)
{
	if (eventMetadata->bitsHLT == 0)
		addLog(eventMetadata, "hlt bits are empty");
	if (eventMetadata->bitsHLT == 1)
		addLog(eventMetadata, "one hltFail bit set");

	for (std::vector<std::string>::iterator it = hlTrigger.begin(); it != hlTrigger.end(); it++)
	{
		if ( find(lumiMetadata->hltNames.begin(), lumiMetadata->hltNames.end(), *it) == lumiMetadata->hltNames.end())
		{
			addLog(eventMetadata, "HLT not found: "+(*it));
			continue;
		}
		unsigned int idx = find(lumiMetadata->hltNames.begin(), lumiMetadata->hltNames.end(), *it) - lumiMetadata->hltNames.begin();

		if (hltPrescale[*it] == 0)
		{
			hltPrescale[*it] = lumiMetadata->hltPrescales[idx];
			continue;
		}
		if (hltPrescale[*it] != lumiMetadata->hltPrescales[idx])
		{
			addLog(eventMetadata, "Change of prescale detected: "+(*it));
			std::cout << "change of prescale for " << (*it) << ": " << lumiMetadata->hltPrescales[idx] << " --> " << hltPrescale[*it] << "\n";
			hltPrescale[*it] = lumiMetadata->hltPrescales[idx];
		}
	}
}

template <typename JetType, typename METType>
void TriggerTest<JetType, METType>::intermediateResults()
{
}

template <typename JetType, typename METType>
void TriggerTest<JetType, METType>::final()
{
	stable_sort (problemLog.begin(), problemLog.end());
  std::vector<std::string>::iterator it = unique (problemLog.begin(), problemLog.end());
  problemLog.resize( it - problemLog.begin() );

	std::cout << "\n\n    === Summary of all Problems ===\n\n";
	for (std::vector<std::string>::iterator it = problemLog.begin(); it != problemLog.end(); it++)
		std::cout << *it << "\n";
	std::cout << std::endl;

	std::cout << "\n";
}

template class TriggerTest<KDataJet, KDataMET>;
template class TriggerTest<KDataPFJet, KDataPFMET>;
