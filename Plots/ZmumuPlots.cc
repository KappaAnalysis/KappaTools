#include "ZmumuPlots.h"

template <typename JetType>
KappaTools::ZmumuPlots<JetType>::ZmumuPlots(TDirectory * tmpFile, TString directory, TString subDirectory)
{
	TDirectory * tmpDirectory = getDirectory(tmpFile, directory, subDirectory);

	Z_mass 						= new TH1D("Z_mass","Z #rightarrow #mu #mu mass", 50, 0., 150.);
	Z_mass_low 				= new TH1D("Z_mass_low","Z #rightarrow #mu #mu mass", 50, 0., 75.);
	Z_mass_zoom 			= new TH1D("Z_mass_zoom","Z #rightarrow #mu #mu mass", 50, 70., 110.);

	Z_pt	 						= new TH1D("Z_pt","#p_{T}^{Z}", 50, 0., 75.);
	Z_pt_full					= new TH1D("Z_pt_full","#p_{T}^{Z}", 100, 0., 1000.);
	Z_eta 						= new TH1D("Z_eta","#eta_{Z}", 50, -5., 5.);
	Z_phi 						= new TH1D("Z_phi","#phi_{Z}", 50, -3.5, 3.5);
	
	zjet_dR						= new TH1D("zjet_dR", "#DeltaR(Z,jet)", 50, 0., 6.5);
	zjet_dPhi					= new TH1D("zjet_dPhi", "#Delta #Phi(Z,jet)", 50, 0., 3.5);


	muons_dR					= new TH1D("muons_dR", "#DeltaR(#mu_{1},#mu_{2})", 50, 0., 6.5);
	muons_dPhi				= new TH1D("muons_dPhi", "#Delta #Phi(#mu_{1},#mu_{2})", 50, 0., 3.5);

	muons_plots				= new KappaTools::StandardMuonPlots(tmpDirectory, "muons", "");
	muon1_plots				= new KappaTools::StandardMuonPlots(tmpDirectory, "muon1", "");
	muon2_plots				= new KappaTools::StandardMuonPlots(tmpDirectory, "muon2", "");

	//jet_plots				= new MTA::StandardJetPlots<MTAPFJet>(tmpDirectory, "jet", "");
}

template <typename JetType>
void KappaTools::ZmumuPlots<JetType>::process(KappaTools::ZmumuObjects<JetType> * zmumu, double weight)
{
	RMLV z = zmumu->getDiMu();
	Z_mass->Fill(z.mass(), weight);
	Z_mass_low->Fill(z.mass(), weight);
	Z_mass_zoom->Fill(z.mass(), weight);

	Z_eta->Fill(z.eta(), weight);
	Z_phi->Fill(z.phi(), weight);
	Z_pt->Fill(z.pt(), weight);
	Z_pt_full->Fill(z.pt(), weight);

	muons_dR->Fill(ROOT::Math::VectorUtil::DeltaR(zmumu->getMuon1()->p4, zmumu->getMuon2()->p4), weight);
	muons_dPhi->Fill(ROOT::Math::VectorUtil::DeltaPhi(zmumu->getMuon1()->p4, zmumu->getMuon2()->p4), weight);

	/*
	if (zmumu->getRJet())
	{
		zjet_dR->Fill(ROOT::Math::VectorUtil::DeltaR(zmumu->p4, zmumu->getRJet()->p4), weight);
		zjet_dPhi->Fill(ROOT::Math::VectorUtil::DeltaPhi(zmumu->p4, zmumu->getRJet()->p4), weight);
	}
	*/
	
	muons_plots->process(zmumu->getMuon1(), zmumu->getPV(), weight);
	muons_plots->process(zmumu->getMuon2(), zmumu->getPV(), weight);
	muon1_plots->process(zmumu->getMuon1(), zmumu->getPV(), weight);
	muon2_plots->process(zmumu->getMuon2(), zmumu->getPV(), weight);

	//jet_plots->process(zmumu->getRJet(), zmumu->getPV(), weight);
}

template <typename JetType>
void KappaTools::ZmumuPlots<JetType>::final()
{

}

//template class KappaTools::ZmumuPlots<MTAPFJet>;

