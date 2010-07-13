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
	std::cout << "di-muon candidate:" << std::endl;
	std::cout << "\t run=" << eventMetadata->nRun << " AND lumi=" << eventMetadata->nLumi << "" << std::endl;
	std::cout << "\t event=" << eventMetadata->nEvent << "" << std::endl;
	std::cout << "\t mass: " << z.mass() << "" << std::endl;
	std::cout << "\t pT = " << z.pt() << "\t";
	std::cout << "\t eta = " << z.eta() << "\t";
	std::cout << "\t phi = " << z.phi() << "" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "\t Muon 1: " << muon1->p4 << "" << std::endl;
	printMuonInformation(muon1);
	std::cout << "" << std::endl;
	std::cout << "\t Muon 2: " << muon2->p4 << "" << std::endl;
	printMuonInformation(muon2);
	std::cout << std::endl << "\t Primaryvertex:" << std::endl;
	if (!primaryvertex)
		std::cout << "\t\t not present!" << std::endl;
	else
	{
		std::cout << "\t\t fake = " << primaryvertex->fake << "" << std::endl;
		std::cout << "\t\t pos = " << primaryvertex->position << "" << std::endl;
		std::cout << "\t\t nTracks = " << primaryvertex->nTracks << "" << std::endl;
		std::cout << "\t\t ndof = " << primaryvertex->nDOF << "" << std::endl;
		std::cout << "\t\t chi2 = " << primaryvertex->chi2 << "" << std::endl;
		std::cout << "\t\t prob = " << TMath::Prob(primaryvertex->chi2, static_cast<int>(primaryvertex->nDOF)) << "" << std::endl;
	}
	if (met)
		std::cout << "\t MET: " << met->p4 << "" << std::endl;
	std::cout << "\t Triggers: ";
	for (unsigned int idx = 0; idx < lumiMetadata->hltNames.size(); idx++)
	{
		if ( eventMetadata->bitsHLT & ((unsigned long long)1 << idx))
			std::cout << lumiMetadata->hltNames[idx] << ", ";
	}
	std::cout << "" << std::endl;
}

template <typename JetType, typename METType>
void KappaTools::ZmumuObjects<JetType, METType>::printMuonInformation(KDataMuon * muon)
{
	std::cout << "\t\t type:                  " << (muon->isGlobalMuon()?"glb ":"--- ") << (muon->isStandAloneMuon()?"sta ":"--- ") << (muon->isTrackerMuon()?"trk ":"--- ")<< "" << std::endl;
	std::cout << "\t\t #chambers:             " << muon->numberOfChambers << "" << std::endl;
	std::cout << "\t\t #matches:              " << muon->numberOfMatches << "" << std::endl;
	std::cout << "\t\t #valid tracker hits:   " << (muon->track.nValidPixelHits+muon->track.nValidStripHits) << "" << std::endl;
	std::cout << "\t\t #valid pixel hits:     " << muon->track.nValidPixelHits << "" << std::endl;
	std::cout << "\t\t #valid muon hits (glb) " << muon->globalTrack.nValidMuonHits << "" << std::endl;
	std::cout << "\t\t vertex:                " << muon->vertex.position << "" << std::endl;
	std::cout << "\t\t ecal iso 03:           " << muon->ecalIso03 << "" << std::endl;
	std::cout << "\t\t hcal iso 03:           " << muon->hcalIso03 << "" << std::endl;
	std::cout << "\t\t track iso 03:          " << muon->trackIso03 << "" << std::endl;
	std::cout << "\t\t chi2/ndof (glb):       " << muon->globalTrack.chi2/muon->globalTrack.nDOF << "" << std::endl;

	std::cout << "\t\t track:                 " << muon->track.p4 << "" << std::endl;
	std::cout << "\t\t IP (trk vs pv):        " << muon->track.getIP(primaryvertex,0) << "" << std::endl;
	std::cout << "\t\t IPsignf. (trk vs pv):  " << muon->track.getIP(primaryvertex,2) << "" << std::endl;
	std::cout << "\t\t IP (trk vs bs):        " << muon->track.getIP(beamspot,0) << "" << std::endl;
	std::cout << "\t\t IPsignf. (trk vs bs):  " << muon->track.getIP(beamspot,2) << "" << std::endl;
	std::cout << "\t\t hltMatch:              ";
	for (unsigned int idx = 0; idx < lumiMetadata->hltNamesMuons.size(); idx++)
	{
		if ( muon->hltMatch & ((unsigned long long)1 << idx))
			std::cout << lumiMetadata->hltNamesMuons[idx] << ", ";
	}
	std::cout << "" << std::endl;
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
