#include "VertexNdofCut.h"
#include "BalancePhiCut.h"
#include "BalancePtCut.h"
#include "MuonTypeCut.h"
#include "IsolationCut.h"

#include "DataFormats/interface/KBasic.h" // to get KDataMET
#include "DataFormats/interface/KMuon.h" // to get KDataMuon

int main()
{
	KappaTools::VertexNdofCut VertexNdofCut_Test;
	KappaTools::BalancePhiCut<KDataTrack,KDataTrack> BalancePhiCut_Test;
	KappaTools::BalancePtCut<KDataTrack,KDataTrack> BalancePtCut_Test;
	KappaTools::MuonTypeCut MuonTypeCut_Test;
	KappaTools::IsolationCut<KDataMuon> IsolationCut_Test;

	return 0;
}
