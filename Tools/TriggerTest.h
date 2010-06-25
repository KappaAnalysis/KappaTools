#ifndef TriggerTest_h
#define TriggerTest_h

#include <vector>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <iostream>

#include "TDirectory.h"

#include "DataFormats/interface/KMetadata.h"
#include "DataFormats/interface/KJetMET.h"

#define Z0_MASS 91.187

template <typename JetType, typename METType>
class TriggerTest
{
	void addLog(KEventMetadata * eventMetadata, std::string text);

	std::vector<std::string> problemLog;

	std::vector<std::string> hlTrigger;
	std::map<std::string, unsigned int> hltPrescale;
public:

	TriggerTest(TDirectory * histofile);

	void processEvent(KEventMetadata * eventMetadata, KLumiMetadata * lumiMetadata);
	void intermediateResults();
	void final();

	std::vector<unsigned long> usedRuns;
};

#endif
