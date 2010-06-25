#include <iostream>
#include <vector>
#include <utility>
#include <fstream>

#include "TH1F.h"
#include "TFile.h"
#include "TChain.h"

#include "../Toolbox/ProgressMonitor.h"

#include "DataFormats/interface/KMetadata.h"

#include "../RootTools/FileInterface.h"

#include "TriggerTest.h"

#include "Toolbox/CmdLineSetup.h"

bool abortProgram = false;

void zmumu(std::vector<std::string> filenames, std::string outputFilename)
{
	FileInterface fi(filenames);

	KEventMetadata * m_eventmetadata;
	KLumiMetadata * m_lumimetadata;
	fi.AssignEventPtr(&m_eventmetadata);

	fi.SpeedupTree();

	Long64_t nentries_reco = fi.eventdata.GetEntries();
	std::cout << nentries_reco << " events\n";

	Long64_t skip_events=0;
	Long64_t max_events =5e9;

	TString filename = outputFilename;

	TFile * histofile = new TFile(filename,"RECREATE");
	TH1F * counter = new TH1F("counter", "counting all events that have been processed", 1, 0, 1);

	TriggerTest<KDataPFJet, KDataPFMET> * triggerTest = 0;

	triggerTest = new TriggerTest<KDataPFJet, KDataPFMET>(histofile);

	unsigned int cnt = 0;
	unsigned int prevRun = 0;
	unsigned int prevLumi = 0;

	ProgressMonitor * timer = new ProgressMonitor(nentries_reco);

	for (unsigned int i=skip_events;i<skip_events+max_events && i<nentries_reco && !abortProgram;i++)
	{
		if (!timer->Update(1+i))
			break;

		if (i % 25000 == 0 && i>0)
			;//triggerTest.intermediateResults();

		fi.eventdata.GetEntry(i);

		if (prevRun!=m_eventmetadata->nRun)
		{
			prevRun=m_eventmetadata->nRun;
			prevLumi=m_eventmetadata->nLumi;
		}
		if (prevLumi!=m_eventmetadata->nLumi)
			prevLumi=m_eventmetadata->nLumi;

		fi.AssignLumiPtr(m_eventmetadata->nRun, m_eventmetadata->nLumi, &m_lumimetadata);

		cnt++;

		triggerTest->processEvent(m_eventmetadata, m_lumimetadata);
	}
	counter->SetBinContent(1, cnt);
	delete timer;

	std::cout << std::endl;
	histofile->Write();

	triggerTest->final();
}

int main(int argc, char* argv[])
{
	CmdLineOptionSwitch<bool> optBatchMode('b', "batch", "Bool", false);
	CmdLineOptionValue<int> optVerbosity('v', "verbosity", "Integer", 1);
	CmdLineOptionValue<std::string> optOutputFile('o', "output", "String", "triggertest.root");
	CmdLineOptionVector<std::string> optJsonFiles('j',"json","String","");

	std::vector<std::string> filenames = CmdLineBase::ParseArgs(argc, argv, OPT_Help | OPT_Version);
	CmdLineBase::Show("");

	//opts.outputFile = optOutputFile.Value();

	if (filenames.size())
	{
		if (optBatchMode)
				std::cout << "running in batch mode...\n";

		zmumu(filenames, optOutputFile);
	}
	else
	{
		std::cout << "No input files specified. Quitting program.\n";
	}
	return 0;
}
