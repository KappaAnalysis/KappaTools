#include "GoodTracksFractionCut.h"
#include "L1TriggerCut.h"
#include "METoverSumEtCut.h"

#include "DataFormats/interface/KBasic.h" // to get KDataMET

int main()
{
	KappaTools::GoodTracksFractionCut GoodTracksFractionCut_Test;
	KappaTools::L1TriggerCut L1TriggerCut_Test;
	KappaTools::METoverSumEtCut<KDataMET> METoverSumEtCut_Test;
	return 0;
}
