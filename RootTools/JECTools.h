#ifndef KAPPA_JECTOOLS_H
#define KAPPA_JECTOOLS_H

#include <CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h>
#include <DataFormats/src/classes.h>
#include "SortTools.h"

template<typename T>
inline void correctSingleJet(T &jet, FactorizedJetCorrector *jec, const double jes = 1)
{
	jec->setJetEta(jet.p4.eta());
	jec->setJetPt(jet.p4.pt());
	jec->setJetE(jet.p4.E());
	jec->setJetPhi(jet.p4.phi());
	jet.p4 *= (jec->getCorrection() * jes);
}

template<>
inline void correctSingleJet(KDataJet &jet, FactorizedJetCorrector *jec, const double jes)
{
	jec->setJetEta(jet.p4.eta());
	jec->setJetPt(jet.p4.pt());
	jec->setJetE(jet.p4.E());
	jec->setJetPhi(jet.p4.phi());
	jec->setJetEMF(jet.fEM);
	jec->setJetA(jet.area);
	jet.p4 *= (jec->getCorrection() * jes);
}

template<>
inline void correctSingleJet(KDataPFJet &jet, FactorizedJetCorrector *jec, const double jes)
{
	jec->setJetEta(jet.p4.eta());
	jec->setJetPt(jet.p4.pt());
	jec->setJetE(jet.p4.E());
	jec->setJetPhi(jet.p4.phi());
	jec->setJetEMF(jet.neutralEMFraction + jet.chargedEMFraction);
	jec->setJetA(jet.area);
	jet.p4 *= (jec->getCorrection() * jes);
}

template<typename T>
inline void correctSingleJet(std::vector<T> *jets, const int idx, FactorizedJetCorrector *jec,
	const double jes = 1, const double rho = 0, const int npv = 0)
{
	jec->setRho(rho);
	jec->setNPV(npv);
	correctSingleJet<T>(jets->at(idx), jec, jes);
}

template<typename T>
inline void correctJets(std::vector<T> *jets, FactorizedJetCorrector *jec,
	const double rho = 0, const int npv = 0)
{
	if (jec == 0)
		return;
	for (size_t i = 0; i < jets->size(); ++i)
	{
		jec->setRho(rho);
		jec->setNPV(npv);
		correctSingleJet(jets, i, jec);
	}
	sort_pt(jets);
}

template<typename T>
inline void applySingleJetJES(std::vector<T> *jets, const int idx, const double jes = 1)
{
	T &tmp = jets->at(idx);
	tmp.p4 *= jes;
}

#endif
