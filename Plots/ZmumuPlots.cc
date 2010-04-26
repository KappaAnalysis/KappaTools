#include "ZmumuPlots.h"

template <typename JetType, typename METType>
KappaTools::ZmumuPlots<JetType, METType>::ZmumuPlots(TDirectory * tmpFile, TString directory, TString subDirectory)
{
	TDirectory * tmpDirectory = getDirectory(tmpFile, directory, subDirectory);

	Z_mass 						= new TH1D("Z_mass","m_{Z #rightarrow #mu #mu mass}", 50, 0., 150.);
	Z_mass_low 				= new TH1D("Z_mass_low","m_{Z #rightarrow #mu #mu mass}", 50, 0., 75.);
	Z_mass_zoom 			= new TH1D("Z_mass_zoom","m_{Z #rightarrow #mu #mu mass}", 50, 70., 110.);

	Z_pt	 						= new TH1D("Z_pt","p_{\\mathrm{T}}^{Z}", 50, 0., 75.);
	Z_pt_full					= new TH1D("Z_pt_full","p_{\\mathrm{T}}^{Z}", 100, 0., 1000.);
	Z_eta 						= new TH1D("Z_eta","#eta_{Z}", 50, -5., 5.);
	Z_phi 						= new TH1D("Z_phi","#phi_{Z}", 50, -3.5, 3.5);

	zjet_dR						= new TH1D("zjet_dR", "#DeltaR(Z,jet)", 50, 0., 6.5);
	zjet_dPhi					= new TH1D("zjet_dPhi", "#Delta #phi(Z,jet)", 50, 0., 3.5);

	muons_dR					= new TH1D("muons_dR", "#DeltaR(#mu_{1},#mu_{2})", 50, 0., 6.5);
	muons_dPhi				= new TH1D("muons_dPhi", "#Delta #phi(#mu_{1},#mu_{2})", 50, 0., 3.5);

	muons_plots				= new KappaTools::StandardMuonPlots(tmpDirectory, "muons", "");
	muon1_plots				= new KappaTools::StandardMuonPlots(tmpDirectory, "muon1", "");
	muon2_plots				= new KappaTools::StandardMuonPlots(tmpDirectory, "muon2", "");

	jet_plots					= new KappaTools::StandardJetPlots<JetType>(tmpDirectory, "jet", "");
}

template <typename JetType, typename METType>
void KappaTools::ZmumuPlots<JetType, METType>::process(KappaTools::ZmumuObjects<JetType, METType> * zmumu, double weight)
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

	if (zmumu->getRJet())
	{
		zjet_dR->Fill(ROOT::Math::VectorUtil::DeltaR(zmumu->p4, zmumu->getRJet()->p4), weight);
		zjet_dPhi->Fill(ROOT::Math::VectorUtil::DeltaPhi(zmumu->p4, zmumu->getRJet()->p4), weight);
	}

	muons_plots->process(zmumu->getMuon1(), zmumu->getPV(), weight);
	muons_plots->process(zmumu->getMuon2(), zmumu->getPV(), weight);
	muon1_plots->process(zmumu->getMuon1(), zmumu->getPV(), weight);
	muon2_plots->process(zmumu->getMuon2(), zmumu->getPV(), weight);

	jet_plots->process(zmumu->getRJet(), zmumu->getPV(), weight);
}

template <typename JetType, typename METType>
void KappaTools::ZmumuPlots<JetType, METType>::final()
{

}


template <typename ZmumuType>
KappaTools::ZmumuNtuple<ZmumuType>::ZmumuNtuple(TDirectory * tmpFile, TString directory, TString subDirectory) : ntuple(0)
{
	getDirectory(tmpFile, directory, subDirectory);
	ntuple = new TNtuple("ntuple", "ntuple", "weight:mass:pt:eta:pt1:pt2:eta1:eta2");
}

template <typename ZmumuType>
void KappaTools::ZmumuNtuple<ZmumuType>::process(ZmumuType * zmumu, double weight)
{
	if (!zmumu)
		return;

	ntuple->Fill(
		weight,
		zmumu->getDiMu().mass(),
		zmumu->getDiMu().pt(),
		zmumu->getDiMu().eta(),
		zmumu->getMuon1()->p4.pt(),
		zmumu->getMuon2()->p4.pt(),
		zmumu->getMuon1()->p4.eta(),
		zmumu->getMuon2()->p4.eta()
	);
}

template <typename ZmumuType>
void KappaTools::ZmumuNtuple<ZmumuType>::final()
{

}

//template class KappaTools::ZmumuPlots<MTAPFJet>;
template class KappaTools::ZmumuPlots<KDataJet, KDataMET>;
template class KappaTools::ZmumuPlots<KDataPFJet, KDataPFMET>;
template class KappaTools::ZmumuNtuple<KappaTools::ZmumuObjects<KDataJet, KDataMET> >;
template class KappaTools::ZmumuNtuple<KappaTools::ZmumuObjects<KDataPFJet, KDataPFMET> >;
