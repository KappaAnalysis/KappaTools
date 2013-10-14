/* Copyright (c) 2011 - All Rights Reserved
 *   Fred Stober <stober@cern.ch>
 *   Manuel Zeise <zeise@cern.ch>
 */

#include "JetID.h"

bool JetIDLoose<KDataJet>::operator()(const struct KDataJet &jet) const
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

bool JetIDLoose<KDataPFJet>::operator()(const struct KDataPFJet &jet) const
{
	if (
		(jet.neutralEMFraction < 0.99) &&
		(jet.neutralHadFraction < 0.99) &&
		(jet.nConst > 1)
		)
	{
		if (fabs(jet.p4.eta()) < 2.4)
		{
			if (
				(jet.chargedEMFraction < 0.99) &&
				(jet.chargedHadFraction > 0) &&
				(jet.nCharged > 0)
				)
				return true;
			return false;
		}
		return true;
	}
	return false;
}

bool JetIDTight<KDataPFJet>::operator()(const class KDataPFJet &jet) const
{
	if (
		(jet.neutralEMFraction < 0.90) &&
		(jet.neutralHadFraction < 0.90) &&
		(jet.nConst > 1)
		)
	{
		if (fabs(jet.p4.eta()) < 2.4)
		{
			if (
				(jet.chargedEMFraction < 0.99) &&
				(jet.chargedHadFraction > 0) &&
				(jet.nCharged > 0)
				)
				return true;
			return false;
		}
		return true;
	}
	return false;
}
