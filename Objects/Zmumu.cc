#include "Zmumu.h"

template <typename JetType, typename METType>
RMLV KappaTools::ZmumuObjects<JetType, METType>::getDiMuP4()
{
	if (!muon1 || !muon2)
		return RMLV();
	return ((RMLV)(muon1->p4)+(RMLV)(muon2->p4));
}

template <typename JetType, typename METType>
void KappaTools::ZmumuObjects<JetType, METType>::printInformation()
{
	RMLV z = getDiMuP4();
	std::cout << "di-muon candidate:\n";
	std::cout << "\t run=" << eventMetadata->nRun << " AND lumi=" << eventMetadata->nLumi << "\n";
	std::cout << "\t event=" << eventMetadata->nEvent << "\n";
	std::cout << "\t mass: " << z.mass() << "\n";
	std::cout << "\t pT = " << z.pt() << "\t";
	std::cout << "\t eta = " << z.eta() << "\t";
	std::cout << "\t phi = " << z.phi() << "\n";
	std::cout << "\n";
	std::cout << "\t Muon 1: " << muon1->p4 << "\n";
	printMuonInformation(muon1);
	std::cout << "\n";
	std::cout << "\t Muon 2: " << muon2->p4 << "\n";
	printMuonInformation(muon2);
	std::cout << "\n\t Primaryvertex:\n";
	if (!primaryvertex)
		std::cout << "\t\t not present!\n";
	else
	{
		std::cout << "\t\t fake = " << primaryvertex->fake << "\n";
		std::cout << "\t\t pos = " << primaryvertex->position << "\n";
		std::cout << "\t\t nTracks = " << primaryvertex->nTracks << "\n";
		std::cout << "\t\t ndof = " << primaryvertex->nDOF << "\n";
		std::cout << "\t\t chi2 = " << primaryvertex->chi2 << "\n";
		std::cout << "\t\t prob = " << TMath::Prob(primaryvertex->chi2, static_cast<int>(primaryvertex->nDOF)) << "\n";
	}
	if (met)
		std::cout << "\t MET: " << met->p4 << "\n";
	std::cout << "\t Triggers: ";
	for (unsigned int idx = 0; idx < lumiMetadata->hltNames.size(); idx++)
	{
		if ( eventMetadata->bitsHLT & ((unsigned long long)1 << idx))
			std::cout << lumiMetadata->hltNames[idx] << ", ";
	}
	std::cout << "\n";
}

template <typename JetType, typename METType>
void KappaTools::ZmumuObjects<JetType, METType>::printMuonInformation(KDataMuon * muon)
{
	std::cout << "\t\t type:                  " << (muon->isGlobalMuon()?"glb ":"--- ") << (muon->isStandAloneMuon()?"sta ":"--- ") << (muon->isTrackerMuon()?"trk ":"--- ")<< "\n";
	std::cout << "\t\t #chambers:             " << muon->numberOfChambers << "\n";
	std::cout << "\t\t #matches:              " << muon->numberOfMatches << "\n";
	std::cout << "\t\t #valid tracker hits:   " << (muon->track.nValidPixelHits+muon->track.nValidStripHits) << "\n";
	std::cout << "\t\t #valid pixel hits:     " << muon->track.nValidPixelHits << "\n";
	std::cout << "\t\t #valid muon hits (glb) " << muon->globalTrack.nValidMuonHits << "\n";
	std::cout << "\t\t vertex:                " << muon->vertex.position << "\n";
	std::cout << "\t\t ecal iso 03:           " << muon->ecalIso03 << "\n";
	std::cout << "\t\t hcal iso 03:           " << muon->hcalIso03 << "\n";
	std::cout << "\t\t track iso 03:          " << muon->trackIso03 << "\n";
	std::cout << "\t\t chi2/ndof (glb):       " << muon->globalTrack.chi2/muon->globalTrack.nDOF << "\n";

	std::cout << "\t\t track:                 " << muon->track.p4 << "\n";
	std::cout << "\t\t IP (trk vs pv):        " << muon->track.getIP(primaryvertex,0) << "\n";
	std::cout << "\t\t IPsignf. (trk vs pv):  " << muon->track.getIP(primaryvertex,2) << "\n";
	std::cout << "\t\t IP (trk vs bs):        " << muon->track.getIP(beamspot,0) << "\n";
	std::cout << "\t\t IPsignf. (trk vs bs):  " << muon->track.getIP(beamspot,2) << "\n";
	std::cout << "\t\t hltMatch:              ";
	for (unsigned int idx = 0; idx < lumiMetadata->hltNamesMuons.size(); idx++)
	{
		if ( muon->hltMatch & ((unsigned long long)1 << idx))
			std::cout << lumiMetadata->hltNamesMuons[idx] << ", ";
	}
	std::cout << "\n";
}

template <typename JetType, typename METType>
void KappaTools::ZmumuObjects<JetType, METType>::recalcP4()
{
	if (!muon1 || !muon2)
		p4 = RMLV();
	else
		p4 = muon1->p4 + muon2->p4;
}

template <typename JetType, typename METType>
void KappaTools::ZmumuObjects<JetType, METType>::setMuons(KDataMuon * muon1_, KDataMuon * muon2_)
{
	muon1 = muon1_;
	muon2 = muon2_;
	recalcP4();
}

template <typename JetType, typename METType>
void KappaTools::ZmumuObjects<JetType, METType>::setRJet(JetType * rjet_)
{
	rjet = rjet_;
}

template <typename JetType, typename METType>
void KappaTools::ZmumuObjects<JetType, METType>::setMET(METType * met_)
{
	met = met_;
}

template <typename JetType, typename METType>
void KappaTools::ZmumuObjects<JetType, METType>::setMetadata(KEventMetadata * eventMetadata_, KLumiMetadata * lumiMetadata_)
{
	eventMetadata = eventMetadata_;
	lumiMetadata = lumiMetadata_;
}

template <typename JetType, typename METType>
void KappaTools::ZmumuObjects<JetType, METType>::setPV(KDataVertex * primaryvertex_)
{
	primaryvertex = primaryvertex_;
}

template <typename JetType, typename METType>
void KappaTools::ZmumuObjects<JetType, METType>::setBS(KDataBeamSpot * beamspot_)
{
	beamspot = beamspot_;
}

template <typename JetType, typename METType>
KDataMuon * KappaTools::ZmumuObjects<JetType, METType>::getMuon1()
{
	return muon1;
}

template <typename JetType, typename METType>
KDataMuon * KappaTools::ZmumuObjects<JetType, METType>::getMuon2()
{
	return muon2;
}

template <typename JetType, typename METType>
JetType * KappaTools::ZmumuObjects<JetType, METType>::getRJet()
{
	return rjet;
}

template <typename JetType, typename METType>
METType * KappaTools::ZmumuObjects<JetType, METType>::getMET()
{
	return met;
}

template <typename JetType, typename METType>
KDataVertex * KappaTools::ZmumuObjects<JetType, METType>::getPV()
{
	return primaryvertex;
}

template <typename JetType, typename METType>
KDataBeamSpot * KappaTools::ZmumuObjects<JetType, METType>::getBS()
{
	return beamspot;
}

template <typename JetType, typename METType>
KEventMetadata * KappaTools::ZmumuObjects<JetType, METType>::getEventMetadata()
{
	return eventMetadata;
}
template <typename JetType, typename METType>
KLumiMetadata * KappaTools::ZmumuObjects<JetType, METType>::getLumiMetadata()
{
	return lumiMetadata;
}

template class KappaTools::ZmumuObjects<KDataJet, KDataMET>;
template class KappaTools::ZmumuObjects<KDataPFJet, KDataMET>;
template class KappaTools::ZmumuObjects<KDataPFJet, KDataPFMET>;
