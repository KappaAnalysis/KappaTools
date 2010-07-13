#include "LumiMetadataProvider.h"

KappaTools::LumiMetadataProvider::LumiMetadataProvider(TTree * lumis_tree)
{
	KLumiMetadata * m_eventinfo = new KLumiMetadata();
	TBranch * b_eventinfo;
	lumis_tree->SetBranchAddress("KLumiMetadata", &m_eventinfo, &b_eventinfo);
	
	Long64_t nentries = lumis_tree->GetEntries();

	std::cout << nentries << " lumi blocks" << std::endl;

	for (unsigned int i=0;i<nentries;i++)
	{
		lumis_tree->GetEntry(i);
		std::pair<unsigned long,unsigned long> idn (m_eventinfo->nRun, m_eventinfo->nLumi);

		tmpLumiMetadatas[idn]=(KLumiMetadata)(*m_eventinfo);
	}
}

KLumiMetadata * KappaTools::LumiMetadataProvider::get(KEventMetadata * eventMetadata)
{
	std::pair<unsigned long,unsigned long> idn (eventMetadata->nRun, eventMetadata->nLumi);
	return &tmpLumiMetadatas[idn];
}
