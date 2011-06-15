#include "JetID.h"

template<>
bool jetIDLoose(const KDataJet &jet)
{
	if (
		((fabs(jet.p4.eta()) > 2.6) || (jet.fEM > 0.01)) &&		// Remove HCAL noise for |eta|
		(jet.fHPD < 0.98) &&	// Remove defective HCAL cells
		(jet.n90Hits > 1)	// Remove ECAL spikes
		)
		return true;
	else
		return false;
}
