/* Copyright (c) 2010 - All Rights Reserved
 *   Fred Stober <stober@cern.ch>
 *   Manuel Zeise <zeise@cern.ch>
 */

#include "JetPlots.h"

namespace KappaTools
{
	template <typename JetType>
	StandardJetPlots<JetType>::StandardJetPlots(TDirectory * tmpFile, TString tmpDirectory)
	{
		getDirectory(tmpFile, tmpDirectory);

		jet_pt 					= new TH1D(("pt"),"p_{T} of muon", 75, 0., 150.);
		jet_pt->Sumw2();
		jet_pt_low		 		= new TH1D(("pt_low"),"p_{T} of muon", 50, 0., 25.);
		jet_pt_low->Sumw2();
		jet_pt_full		 		= new TH1D(("pt_full"),"p_{T} of muon", 100, 0., 1000.);
		jet_pt_full->Sumw2();
		jet_eta 				= new TH1D(("eta"),"#eta of muon", 50, -5., 5.);
		jet_eta->Sumw2();
		jet_eta_zoom			= new TH1D("eta_zoom","#eta of muon", 50, -2.5, 2.5);
		jet_eta_zoom->Sumw2();
		jet_phi					= new TH1D(("phi"),"#phi of muon", 50, -3.5, 3.5);
		jet_phi->Sumw2();

		nConstituents = new TH1D("nConstituents","number of constituents", 50, 0, 50);
		nConstituents->Sumw2();
		emFraction = new TH1D("emFraction", "electromagnetic fraction", 50, 0., 1.);
		emFraction->Sumw2();
		hadFraction = new TH1D("hadFraction", "hadronic fraction", 50, 0., 1.);
		hadFraction->Sumw2();

		initSpecific();
	}

	template <typename JetType>
	void StandardJetPlots<JetType>::process(JetType * jet, KVertex * pv, double weight)
	{
		if (!jet)
			return;

		jet_pt->Fill(jet->p4.pt(), weight);
		jet_pt_low->Fill(jet->p4.pt(), weight);
		jet_pt_full->Fill(jet->p4.pt(), weight);
		jet_eta->Fill(jet->p4.eta(), weight);
		jet_eta_zoom->Fill(jet->p4.eta(), weight);
		jet_phi->Fill(jet->p4.phi(), weight);

		nConstituents->Fill(jet->nConstituents, weight);
		//emFraction->Fill(jet->fEM, weight);
		//hadFraction->Fill(1.-jet->fEM, weight);

		processSpecific(jet, pv, weight);
	}

	template <typename JetType>
	void StandardJetPlots<JetType>::final()
	{
	}

	template <>
	void StandardJetPlots<KBasicJet>::initSpecific()
	{
		neutralEmFraction = new TH1D("neutralEmFraction", "neutral electromagnetic fraction", 50, 0., 1.);
		neutralEmFraction->Sumw2();
		chargedEmFraction = new TH1D("chargedEmFraction", "charged electromagnetic fraction", 50, 0., 1.);
		chargedEmFraction->Sumw2();
		neutralHadronFraction = new TH1D("neutralHadronFraction", "neutral electromagnetic fraction", 50, 0., 1.);
		neutralHadronFraction->Sumw2();
		chargedHadronFraction = new TH1D("chargedHadronFraction", "charged electromagnetic fraction", 50, 0., 1.);
		chargedHadronFraction->Sumw2();
	}

	template <typename JetType>
	void StandardJetPlots<JetType>::initSpecific()
	{
	}

	template <>
	void StandardJetPlots<KBasicJet>::processSpecific(KBasicJet * jet, KVertex * pv, double weight)
	{
		if (!jet)
			return;
		neutralEmFraction->Fill(jet->photonFraction, weight);
		chargedEmFraction->Fill(jet->electronFraction, weight);
		neutralHadronFraction->Fill(jet->neutralHadronFraction, weight);
		chargedHadronFraction->Fill(jet->chargedHadronFraction, weight);
	}

	template <typename JetType>
	void StandardJetPlots<JetType>::processSpecific(JetType * jet, KVertex * pv, double weight)
	{
	}
}

template class KappaTools::StandardJetPlots<KCaloJet>;
template class KappaTools::StandardJetPlots<KBasicJet>;
