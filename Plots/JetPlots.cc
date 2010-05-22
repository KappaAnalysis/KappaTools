#include "JetPlots.h"

namespace KappaTools
{
	template <typename JetType>
	StandardJetPlots<JetType>::StandardJetPlots(TDirectory * tmpFile, TString tmpDirectory)
	{
		getDirectory(tmpFile, tmpDirectory);

		jet_pt 					= new TH1D(("pt"),"p_{T} of muon", 75, 0., 150.);
		jet_pt_low		 		= new TH1D(("pt_low"),"p_{T} of muon", 50, 0., 25.);
		jet_pt_full		 		= new TH1D(("pt_full"),"p_{T} of muon", 100, 0., 1000.);
		jet_eta 					= new TH1D(("eta"),"#eta of muon", 50, -5., 5.);
		jet_eta_zoom			= new TH1D("eta_zoom","#eta of muon", 50, -2.5, 2.5);
		jet_phi					= new TH1D(("phi"),"#phi of muon", 50, -3.5, 3.5);

		n90 = new TH1D("n90","number of constituents carrying 0.9 of the energy", 50, 0, 50);
		nConstituents = new TH1D("nConstituents","number of constituents", 50, 0, 50);
		emFraction = new TH1D("emFraction", "electromagnetic fraction", 50, 0., 1.);
		hadFraction = new TH1D("hadFraction", "hadronic fraction", 50, 0., 1.);

		initSpecific();
	}

	template <typename JetType>
	void StandardJetPlots<JetType>::process(JetType * jet, KDataVertex * pv, double weight)
	{
		if (!jet)
			return;

		jet_pt->Fill(jet->p4.pt(), weight);
		jet_pt_low->Fill(jet->p4.pt(), weight);
		jet_pt_full->Fill(jet->p4.pt(), weight);
		jet_eta->Fill(jet->p4.eta(), weight);
		jet_eta_zoom->Fill(jet->p4.eta(), weight);
		jet_phi->Fill(jet->p4.phi(), weight);

		n90->Fill(jet->n90, weight);
		nConstituents->Fill(jet->nConst, weight);
		emFraction->Fill(jet->emf, weight);
		hadFraction->Fill(1.-jet->emf, weight);

		processSpecific(jet, pv, weight);
	}

	template <typename JetType>
	void StandardJetPlots<JetType>::final()
	{
	}

	template <>
	void StandardJetPlots<KDataPFJet>::initSpecific()
	{
		neutralEmFraction = new TH1D("neutralEmFraction", "neutral electromagnetic fraction", 50, 0., 1.);
		chargedEmFraction = new TH1D("chargedEmFraction", "charged electromagnetic fraction", 50, 0., 1.);
		neutralHadFraction = new TH1D("neutralHadFraction", "neutral electromagnetic fraction", 50, 0., 1.);
		chargedHadFraction = new TH1D("chargedHadFraction", "charged electromagnetic fraction", 50, 0., 1.);
	}

	template <typename JetType>
	void StandardJetPlots<JetType>::initSpecific()
	{
	}

	template <>
	void StandardJetPlots<KDataPFJet>::processSpecific(KDataPFJet * jet, KDataVertex * pv, double weight)
	{
		if (!jet)
			return;
		neutralEmFraction->Fill(jet->neutralEmFraction, weight);
		chargedEmFraction->Fill(jet->chargedEmFraction, weight);
		neutralHadFraction->Fill(jet->neutralHadFraction, weight);
		chargedHadFraction->Fill(jet->chargedHadFraction, weight);
	}

	template <typename JetType>
	void StandardJetPlots<JetType>::processSpecific(JetType * jet, KDataVertex * pv, double weight)
	{
	}
}

template class KappaTools::StandardJetPlots<KDataJet>;
template class KappaTools::StandardJetPlots<KDataPFJet>;
