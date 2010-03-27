#include "Zmumu.h"

template <typename JetType>
RMLV KappaTools::ZmumuObjects<JetType>::getDiMuP4()
{
	if (!muon1 || !muon2)
		return RMLV();
	return ((RMLV)(muon1->p4)+(RMLV)(muon2->p4));
}

template <typename JetType>
void KappaTools::ZmumuObjects<JetType>::printInformation()
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

template <typename JetType>
void KappaTools::ZmumuObjects<JetType>::printMuonInformation(KDataMuon * muon)
{
	std::cout << "\t\t #chambers:    " << muon->numberOfChambers << "\n";
	std::cout << "\t\t #track hits:  " << muon->trackHits << "\n";
	std::cout << "\t\t vertex:       " << muon->vertex.position << "\n";												
	std::cout << "\t\t ecal iso 03:  " << muon->ecalIso03 << "\n";
	std::cout << "\t\t hcal iso 03:  " << muon->hcalIso03 << "\n";
	std::cout << "\t\t track iso 03: " << muon->trackIso03 << "\n";
}

template <typename JetType>
void KappaTools::ZmumuObjects<JetType>::recalcP4()
{
	if (!muon1 || !muon2)
		p4 = RMLV();
	else
		p4 = muon1->p4 + muon2->p4;
}

template <typename JetType>
void KappaTools::ZmumuObjects<JetType>::setMuons(KDataMuon * muon1_, KDataMuon * muon2_)
{
	muon1 = muon1_;
	muon2 = muon2_;
	recalcP4();
}

template <typename JetType>
void KappaTools::ZmumuObjects<JetType>::setRJet(JetType * rjet_)
{
	rjet = rjet_;
}

/*
template <typename JetType>
void KappaTools::ZmumuObjects<JetType>::setMET(MTAPFMET * met_)
{
	met = met_;
}

template <typename JetType>
void KappaTools::ZmumuObjects<JetType>::setTrigger(MTATrigger * trigger_)
{
	trigger = trigger_;
}
*/

template <typename JetType>
void KappaTools::ZmumuObjects<JetType>::setPV(KDataVertex * primaryvertex_)
{
	primaryvertex = primaryvertex_;
}

template <typename JetType>
KDataMuon * KappaTools::ZmumuObjects<JetType>::getMuon1()
{
	return muon1;
}

template <typename JetType>
KDataMuon * KappaTools::ZmumuObjects<JetType>::getMuon2()
{
	return muon2;
}

template <typename JetType>
JetType * KappaTools::ZmumuObjects<JetType>::getRJet()
{
	return rjet;
}

template <typename JetType>
KDataVertex * KappaTools::ZmumuObjects<JetType>::getPV()
{
	return primaryvertex;
}

//template class KappaTools::ZmumuObjects<MTAPFJet>;
template class KappaTools::ZmumuObjects<KDataJet>;
