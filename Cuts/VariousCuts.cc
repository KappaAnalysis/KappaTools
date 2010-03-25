#include "VertexNdofCut.h"
#include "BalancePhiCut.h"
#include "BalancePtCut.h"

#include "DataFormats/interface/KBasic.h" // to get KDataMET

int main()
{
	KappaTools::VertexNdofCut VertexNdofCut_Test;
	KappaTools::BalancePhiCut<KDataTrack,KDataTrack> BalancePhiCut_Test;
	KappaTools::BalancePtCut<KDataTrack,KDataTrack> BalancePtCut_Test;

	return 0;
}
