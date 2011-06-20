#ifndef KAPPA_JECTOOLS_H
#define KAPPA_JECTOOLS_H

#include <CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h>
#include <CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h>
#include <Kappa/DataFormats/interface/Kappa.h>
#include "SortTools.h"

enum JECValueType { jec_center, jec_up, jec_down };

// Functions to setup the FactorizedJetCorrector / JetCorrectionUncertainty object

template<typename Tprov, typename Tjet>
inline void setupFactorProvider(const Tjet &jet, Tprov *prov)
{
	prov->setJetEta(jet.p4.eta());
	prov->setJetPt(jet.p4.pt());
	prov->setJetE(jet.p4.E());
	prov->setJetPhi(jet.p4.phi());
}

template<typename Tprov>
inline void setupFactorProvider(const KDataJet &jet, Tprov *prov)
{
	prov->setJetEta(jet.p4.eta());
	prov->setJetPt(jet.p4.pt());
	prov->setJetE(jet.p4.E());
	prov->setJetPhi(jet.p4.phi());
	prov->setJetEMF(jet.fEM);
}

template<typename Tprov>
inline void setupFactorProvider(const KDataPFJet &jet, Tprov *prov)
{
	prov->setJetEta(jet.p4.eta());
	prov->setJetPt(jet.p4.pt());
	prov->setJetE(jet.p4.E());
	prov->setJetPhi(jet.p4.phi());
	prov->setJetEMF(jet.neutralEMFraction + jet.chargedEMFraction);
}

// Functions to correct a single jet with the FactorizedJetCorrector

template<typename T>
inline void correctSingleJet(T &jet, FactorizedJetCorrector *jec)
{
	setupFactorProvider(jet, jec);
	jet.p4 *= jec->getCorrection();
}

template<>
inline void correctSingleJet(KDataJet &jet, FactorizedJetCorrector *jec)
{
	setupFactorProvider(jet, jec);
	jec->setJetA(jet.area);
	jet.p4 *= jec->getCorrection();
}

template<>
inline void correctSingleJet(KDataPFJet &jet, FactorizedJetCorrector *jec)
{
	setupFactorProvider(jet, jec);
	jec->setJetA(jet.area);
	jet.p4 *= jec->getCorrection();
}

// Functions to apply correction + uncertainty to a single jet:

template<typename T>
inline void applyUncertainty(T &jet, JetCorrectionUncertainty *unc, const JECValueType jv = jec_center)
{
	if (jv != jec_center)
	{
		setupFactorProvider(jet, unc);
		jet.p4 *= unc->getUncertainty(jv == jec_up);
	}
}

template<typename T>
inline void correctJets(std::vector<T> *jets,
	FactorizedJetCorrector *jec, JetCorrectionUncertainty *unc,
	const double rho, const int npv, const double area = -1, const JECValueType jv = jec_center)
{
	if (jec == 0)
		return;
	for (size_t idx = 0; idx < jets->size(); ++idx)
	{
		jec->setRho(rho);
		jec->setNPV(npv);
		T &jet = jets->at(idx);
		if (area > 0)
			jet.area = area;
		correctSingleJet(jet, jec);
		if (unc != 0)
			applyUncertainty(jet, unc, jv);
	}
	sort_pt(jets);
}

#endif
