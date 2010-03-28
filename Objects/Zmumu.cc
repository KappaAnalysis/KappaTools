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
}

template <typename JetType, typename METType>
void KappaTools::ZmumuObjects<JetType, METType>::printMuonInformation(KDataMuon * muon)
{
	std::cout << "\t\t #chambers:    " << muon->numberOfChambers << "\n";
	std::cout << "\t\t #track hits:  " << muon->trackHits << "\n";
	std::cout << "\t\t vertex:       " << muon->vertex.position << "\n";												
	std::cout << "\t\t ecal iso 03:  " << muon->ecalIso03 << "\n";
	std::cout << "\t\t hcal iso 03:  " << muon->hcalIso03 << "\n";
	std::cout << "\t\t track iso 03: " << muon->trackIso03 << "\n";
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
void KappaTools::ZmumuObjects<JetType, METType>::setMetadata(KEventMetadata * eventMetadata_)
{
	eventMetadata = eventMetadata_;
}

template <typename JetType, typename METType>
void KappaTools::ZmumuObjects<JetType, METType>::setPV(KDataVertex * primaryvertex_)
{
	primaryvertex = primaryvertex_;
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
KDataVertex * KappaTools::ZmumuObjects<JetType, METType>::getPV()
{
	return primaryvertex;
}

//template class KappaTools::ZmumuObjects<MTAPFJet>;
template class KappaTools::ZmumuObjects<KDataJet, KDataPFMET>;
