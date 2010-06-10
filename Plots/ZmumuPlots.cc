#include "ZmumuPlots.h"

template <typename JetType, typename METType>
KappaTools::ZmumuPlots<JetType, METType>::ZmumuPlots(TDirectory * tmpFile, TString directory)
{
	TDirectory * tmpDirectory = getDirectory(tmpFile, directory);

	Z_mass 						= new TH1D("Z_mass","m_{Z #rightarrow #mu #mu mass}", 40, 0., 200.);
	Z_mass_fine				= new TH1D("Z_mass_fine","m_{Z #rightarrow #mu #mu mass}", 200, 0., 200.);
	Z_mass_low 				= new TH1D("Z_mass_low","m_{Z #rightarrow #mu #mu mass}", 50, 0., 75.);
	Z_mass_zoom 			= new TH1D("Z_mass_zoom","m_{Z #rightarrow #mu #mu mass}", 60, 60., 120.);

	Z_pt	 						= new TH1D("Z_pt","p_{\\mathrm{T}}^{Z}", 50, 0., 75.);
	Z_pt_full					= new TH1D("Z_pt_full","p_{\\mathrm{T}}^{Z}", 100, 0., 1000.);
	Z_eta 						= new TH1D("Z_eta","#eta_{Z}", 50, -5., 5.);
	Z_phi 						= new TH1D("Z_phi","#phi_{Z}", 50, -3.5, 3.5);

	jet_response			= new TH1D("jet_response", "p_{\\mathrm{T}}^{\\mathrm{jet}} / p_{\\mathrm{T}}^{Z}", 100, 0., 2.);
	jet_response_mpf	= new TH1D("jet_response_mpf", "p_{\\mathrm{T}}^{\\mathrm{jet}} / p_{\\mathrm{T}}^{Z} (\\mathrm{MPF})", 100, 0., 2.);

	zjet_dR						= new TH1D("zjet_dR", "#DeltaR(Z,jet)", 50, 0., 6.5);
	zjet_dPhi					= new TH1D("zjet_dPhi", "#Delta #phi(Z,jet)", 50, -1.*M_PI, M_PI);
	zjet_dPhi_zoom		= new TH1D("zjet_dPhi_zoom", "#Delta #phi(Z,jet)", 100, -0.4, +0.4);

	muons_dR					= new TH1D("muons_dR", "#DeltaR(#mu_{1},#mu_{2})", 50, 0., 6.5);
	muons_dPhi				= new TH1D("muons_dPhi", "#Delta #phi(#mu_{1},#mu_{2})", 50, 0., 3.5);

	mumu_vtx_dd				= new TH1D("mumu_vtx_dd", "euklidean dist. between muons' vertices", 100, 0., 1.);
	mumu_vtx_dr				= new TH1D("mumu_vtx_dr", "euklidean dist. between muons' vertices in perp. plane", 100, 0., 0.1);
	mumu_vtx_dz				= new TH1D("mumu_vtx_dz", "euklidean dist. between muons' vertices in z direction", 100, -1., 1.);

	muons_plots				= new KappaTools::StandardMuonPlots(tmpDirectory, "muons");
	muon1_plots				= new KappaTools::StandardMuonPlots(tmpDirectory, "muon1");
	muon2_plots				= new KappaTools::StandardMuonPlots(tmpDirectory, "muon2");

	jet_plots					= new KappaTools::StandardJetPlots<JetType>(tmpDirectory, "jet");
}

template <typename JetType, typename METType>
void KappaTools::ZmumuPlots<JetType, METType>::process(KappaTools::ZmumuObjects<JetType, METType> * zmumu, double weight)
{
	RMLV z = zmumu->getDiMu();
	Z_mass->Fill(z.mass(), weight);
	Z_mass_low->Fill(z.mass(), weight);
	Z_mass_zoom->Fill(z.mass(), weight);
	Z_mass_fine->Fill(z.mass(), weight);

	Z_eta->Fill(z.eta(), weight);
	Z_phi->Fill(z.phi(), weight);
	Z_pt->Fill(z.pt(), weight);
	Z_pt_full->Fill(z.pt(), weight);

	muons_dR->Fill(ROOT::Math::VectorUtil::DeltaR(zmumu->getMuon1()->p4, zmumu->getMuon2()->p4), weight);
	muons_dPhi->Fill(ROOT::Math::VectorUtil::DeltaPhi(zmumu->getMuon1()->p4, zmumu->getMuon2()->p4), weight);

	mumu_vtx_dd->Fill(ROOT::Math::VectorUtil::DeltaR(zmumu->getMuon1()->track.ref,zmumu->getMuon2()->track.ref),weight);
	mumu_vtx_dr->Fill(std::sqrt((zmumu->getMuon1()->track.ref.x()-zmumu->getMuon2()->track.ref.x())*(zmumu->getMuon1()->track.ref.x()-zmumu->getMuon2()->track.ref.x())+(zmumu->getMuon1()->track.ref.y()-zmumu->getMuon2()->track.ref.y())*(zmumu->getMuon1()->track.ref.y()-zmumu->getMuon2()->track.ref.y())),weight);
	mumu_vtx_dz->Fill(zmumu->getMuon1()->track.ref.z()-zmumu->getMuon2()->track.ref.z(),weight);

	if (zmumu->getRJet())
	{
		//if (zmumu->p4.pt()>20 && zmumu->p4.pt()<30)
		jet_response->Fill(zmumu->getRJet()->p4.pt()/zmumu->p4.pt(), weight);

		if (zmumu->getMET())
		{
			RMLV met = (RMLV)zmumu->getMET()->p4;
			double Rmpf=1 + (met.x()*z.x() + met.y()*z.y())/z.perp2();
			jet_response_mpf->Fill(Rmpf, weight);
		}
		zjet_dR->Fill(ROOT::Math::VectorUtil::DeltaR(zmumu->p4, zmumu->getRJet()->p4), weight);
		zjet_dPhi->Fill(ROOT::Math::VectorUtil::Phi_mpi_pi(ROOT::Math::VectorUtil::DeltaPhi(zmumu->p4,zmumu->getRJet()->p4)-M_PI), weight);
		zjet_dPhi_zoom->Fill(ROOT::Math::VectorUtil::Phi_mpi_pi(ROOT::Math::VectorUtil::DeltaPhi(zmumu->p4,zmumu->getRJet()->p4)-M_PI), weight);
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
KappaTools::ZmumuNtuple<ZmumuType>::ZmumuNtuple(TDirectory * tmpFile, TString directory) : ntuple(0)
{
	getDirectory(tmpFile, directory);
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
template class KappaTools::ZmumuPlots<KDataPFJet, KDataMET>;
template class KappaTools::ZmumuNtuple<KappaTools::ZmumuObjects<KDataJet, KDataMET> >;
template class KappaTools::ZmumuNtuple<KappaTools::ZmumuObjects<KDataPFJet, KDataPFMET> >;
template class KappaTools::ZmumuNtuple<KappaTools::ZmumuObjects<KDataPFJet, KDataMET> >;
