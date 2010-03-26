#include "MuonPlots.h"

namespace KappaTools
{
	StandardMuonPlots::StandardMuonPlots(TDirectory * tmpFile, TString tmpDirectory, TString tmpSubDirectory)
	{
		getDirectory(tmpFile, tmpDirectory, tmpSubDirectory);

		muon_pt 					= new TH1D("pt","p_{T} of muon", 75, 0., 150.);
		muon_pt_low		 		= new TH1D("pt_low","p_{T} of muon", 50, 0., 25.);
		muon_eta 					= new TH1D("eta","#eta of muon", 50, -5., 5.);
		muon_eta_zoom			= new TH1D("eta_zoom","#eta of muon", 50, -2.5, 2.5);
		muon_phi					= new TH1D("phi","#phi of muon", 50, -3.5, 3.5);

		muon_ecalIso03		= new TH1D("ecalIso03","ecal isolation 0.3 of muon", 50, 0, 5.);
		muon_hcalIso03		= new TH1D("hcalIso03","hcal isolation 0.3 of muon", 50, 0, 5.);
		muon_trackIso03		= new TH1D("trackIso03","track isolation 0.3 of muon", 50, 0, 5.);

		muon_ecalIso06		= new TH1D("ecalIso06","ecal isolation 0.6 of muon", 50, 0, 5.);
		muon_hcalIso06		= new TH1D("hcalIso06","hcal isolation 0.6 of muon", 50, 0, 5.);
		muon_trackIso06		= new TH1D("trackIso06","track isolation 0.6 of muon", 50, 0, 5.0);

		muon_type					= new TH1D("type","type of muon (is, tracker, calo, sta, global)", 10, 0, 5);

		muon_trackHits					= new TH1D("trackHits","number of muon track hits", 50, 0., 50.);
		muon_numberOfChambers		= new TH1D("numberOfChambers","number of muon chambers", 20, 0., 20.);

		vertex_chi2					= new TH1D("vertex_chi2","#chi^{2} of muon vertex", 50, 0., 50.);
		vertex_ndof					= new TH1D("vertex_ndof","ndof of muon vertex", 25, 0., 25.);
		vertex_chi2norm			= new TH1D("vertex_chi2norm","norm. #chi^{2} of muon vertex", 10, 0., 10.);
		vertex_chi2prob			= new TH1D("vertex_chi2prob","prob(#chi^{2}) of muon vertex", 50, 0., 1.);

		IP								= new TH1D("IP","impact parameter of muon track", 50, -0.1, 0.1);
		IPSig							= new TH1D("IPSig","impact parameter of muon track over uncertainty of track and PV", 50, -10, 10);
		IPvsIPSig					= new TH2D("IPvsIPSig","impact parameter of muon track vs. sign. version of IP", 50, -0.1, 0.1, 50, -10, 10);

		track_chi2					= new TH1D("track_chi2","#chi^{2} of muon track", 50, 0., 50.);
		track_ndof					= new TH1D("track_ndof","ndof of muon track", 50, 0., 50.);
		track_chi2norm			= new TH1D("track_chi2norm","norm. #chi^{2} of muon track", 50, 0., 25.);
		track_chi2prob			= new TH1D("track_chi2prob","prob(#chi^{2}) of muon track", 50, 0., 1.);
	}
	void StandardMuonPlots::process(KDataMuon * muon, KDataVertex * pv, double weight)
	{
		muon_pt->Fill(muon->p4.pt(), weight);
		muon_pt_low->Fill(muon->p4.pt(), weight);
		muon_eta->Fill(muon->p4.eta(), weight);
		muon_eta_zoom->Fill(muon->p4.eta(), weight);
		muon_phi->Fill(muon->p4.phi(), weight);

		muon_ecalIso03->Fill(muon->ecalIso03, weight);
		muon_hcalIso03->Fill(muon->hcalIso03, weight);
		muon_trackIso03->Fill(muon->trackIso03, weight);

		muon_ecalIso06->Fill(muon->ecalIso06, weight);
		muon_hcalIso06->Fill(muon->hcalIso06, weight);
		muon_trackIso06->Fill(muon->trackIso06, weight);

		if (pv)
		{
			IP->Fill(muon->track.getIP(pv,0), weight);
			IPSig->Fill(muon->track.getIP(pv,2), weight);
			IPvsIPSig->Fill(muon->track.getIP(pv,0),muon->track.getIP(pv,2), weight);
		}

		vertex_chi2->Fill(muon->vertex.chi2, weight);
		vertex_ndof->Fill(muon->vertex.nDOF, weight);
		vertex_chi2norm->Fill(muon->vertex.chi2/muon->vertex.nDOF, weight);
		vertex_chi2prob->Fill(TMath::Prob(muon->vertex.chi2, muon->vertex.nDOF), weight);

		track_chi2->Fill(muon->track.chi2, weight);
		track_ndof->Fill(muon->track.nDOF, weight);
		track_chi2norm->Fill(muon->track.chi2/muon->track.nDOF, weight);
		track_chi2prob->Fill(TMath::Prob(muon->track.chi2, muon->track.nDOF), weight);

		muon_trackHits->Fill(muon->trackHits, weight);
		muon_numberOfChambers->Fill(muon->numberOfChambers, weight);

		muon_type->Fill(0., weight);
		if (muon->isTrackerMuon)
			muon_type->Fill(1., weight);
		if (muon->isCaloMuon)
			muon_type->Fill(2., weight);
		if (muon->isStandAloneMuon)
			muon_type->Fill(3., weight);
		if (muon->isGlobalMuon)
			muon_type->Fill(4., weight);
	}
	void StandardMuonPlots::final()
	{
	}
}

