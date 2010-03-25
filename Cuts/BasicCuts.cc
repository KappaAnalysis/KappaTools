#include "BaseCut.h"
#include "CutGroup.h"
#include "NoneCut.h"
#include "ExistenceCut.h"
#include "PtCut.h"
#include "EtaCut.h"
#include "InvariantMassCut.h"
#include "DeltaRCut.h"
#include "ChargeCut.h"

#include "DataFormats/interface/KBasic.h" // to get KDataTrack

int main()
{
	KappaTools::NoneCut NoneCut_Test;
	KappaTools::ExistenceCut<KDataTrack> ExistenceCut_Test;
	KappaTools::PtCut<KDataTrack> PtCut_Test;
	KappaTools::EtaCut<KDataTrack> EtaCut_Test;
	KappaTools::InvariantMassCut<KDataTrack> InvariantMassCut_Test;
	KappaTools::DeltaRCut<KDataTrack, KDataTrack> DeltaRCut_Test;
	KappaTools::ChargeCut<KDataTrack> ChargeCut_Test;

	return 0;
}
