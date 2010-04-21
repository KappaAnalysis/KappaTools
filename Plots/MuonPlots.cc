#include "MuonPlots.h"

namespace KappaTools
{
	StandardMuonPlots::StandardMuonPlots(TDirectory * tmpFile_, TString tmpDirectory_, TString tmpSubDirectory_)
	{
		TDirectory * tmpDirectory = getDirectory(tmpFile_, tmpDirectory_, tmpSubDirectory_);

		muon_pt 					= new TH1D("pt","p_{\\mathrm{T}}", 75, 0., 150.);
		muon_pt_low		 		= new TH1D("pt_low","p_{\\mathrm{T}}", 50, 0., 25.);
		muon_eta 					= new TH1D("eta","#eta", 50, -5., 5.);
		muon_eta_zoom			= new TH1D("eta_zoom","#eta", 50, -2.5, 2.5);
		muon_phi					= new TH1D("phi","#phi", 50, -3.5, 3.5);

		muon_ecalIso03		= new TH1D("ecalIso03","\\mathrm{iso}_{\\mathrm{ecal}}(0.3)", 50, 0, 5.);
		muon_hcalIso03		= new TH1D("hcalIso03","\\mathrm{iso}_{\\mathrm{hcal}}(0.3)", 50, 0, 5.);
		muon_trackIso03		= new TH1D("trackIso03","\\mathrm{iso}_{\\mathrm{trk.}}(0.3)", 50, 0, 5.);

		muon_ecalIso06		= new TH1D("ecalIso06","\\mathrm{iso}_{\\mathrm{ecal}}(0.6)", 50, 0, 5.);
		muon_hcalIso06		= new TH1D("hcalIso06","\\mathrm{iso}_{\\mathrm{hcal}}(0.6)", 50, 0, 5.);
		muon_trackIso06		= new TH1D("trackIso06","\\mathrm{iso}_{\\mathrm{trk.}}(0.6)", 50, 0, 5.0);

		muon_type					= new TH1D("type","\\mathrm{muon\\,\\,type:\\,\\,exists,\\,\\,tracker,\\,\\,calo,\\,\\,sta,\\,\\,global}", 10, 0, 5);

		muon_trackHits					= new TH1D("trackHits","number of muon track hits", 50, 0., 50.);
		muon_numberOfChambers		= new TH1D("numberOfChambers","number of muon chambers", 20, 0., 20.);

		vertex_chi2					= new TH1D("vertex_chi2","#chi^{2}_{\\mathrm{vertex}}", 50, 0., 50.);
		vertex_ndof					= new TH1D("vertex_ndof","\\mathrm{ndof}_{\\mathrm{vertex}}", 25, 0., 25.);
		vertex_chi2norm			= new TH1D("vertex_chi2norm","#chi^{2} / \\mathrm{ndof}", 10, 0., 10.);
		vertex_chi2prob			= new TH1D("vertex_chi2prob","\\mathrm{prob}(#chi^{2})", 50, 0., 1.);

		IP								= new TH1D("IP","\\mathrm{IP}", 50, -0.1, 0.1);
		IPSig							= new TH1D("IPSig","\\mathrm{IP}_\\mathrm{signif.}", 50, -10, 10);
		IPvsIPSig					= new TH2D("IPvsIPSig","\\mathrm{IP\\,\\,vs\\,\\,IP}_\\mathrm{signif.}", 50, -0.1, 0.1, 50, -10, 10);

		caloComp	= new TH1D("caloComp","\\mathrm{calo\\,\\,compatibility}", 100, 0., 1.);
		segComp		= new TH1D("segComp","\\mathrm{segment\\,\\,compatibility}", 100, 0., 1.);

		track = new KappaTools::StandardTrackPlots(tmpDirectory, "track", "");
		innerTrack = new KappaTools::StandardTrackPlots(tmpDirectory, "innerTrack", "");
		globalTrack = new KappaTools::StandardTrackPlots(tmpDirectory, "globalTrack", "");
	}
	void StandardMuonPlots::process(KDataMuon * muon, KDataVertex * pv, double weight)
	{
		if (!muon)
			return;

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

		caloComp->Fill(muon->caloComp, weight);
		segComp->Fill(muon->segComp, weight);

		track->process(&muon->track, pv, weight);
		innerTrack->process(&muon->innerTrack, pv, weight);
		globalTrack->process(&muon->globalTrack, pv, weight);
	}
	void StandardMuonPlots::final()
	{
	}

	template <typename T>
	MuonPlotsByType<T>::MuonPlotsByType(TDirectory * tmpFile, TString tmpDirectory, TString tmpSubDirectory)
	{
		TDirectory * curDirectory = getDirectory(tmpFile, tmpDirectory, tmpSubDirectory);

		allMuons = new KappaTools::StandardMuonPlots(curDirectory, "all", "");
		trackerMuons = new KappaTools::StandardMuonPlots(curDirectory, "tracker", "");
		caloMuons = new KappaTools::StandardMuonPlots(curDirectory, "calo", "");
		standaloneMuons = new KappaTools::StandardMuonPlots(curDirectory, "standalone", "");
		globalMuons = new KappaTools::StandardMuonPlots(curDirectory, "global", "");
	}

	template <typename T>
	void MuonPlotsByType<T>::process(KDataMuon * muon, KDataVertex * pv, double weight)
	{
		if (!muon)
			return;

		allMuons->process(muon, pv, weight);
		if (muon->type & (1<<0))
			trackerMuons->process(muon, pv, weight);
		if (muon->type & (1<<1))
			caloMuons->process(muon, pv, weight);
		if (muon->type & (1<<2))
			standaloneMuons->process(muon, pv, weight);
		if (muon->type & (1<<3))
			globalMuons->process(muon, pv, weight);
	}

	template <typename T>
	void MuonPlotsByType<T>::final()
	{
	}

	template class MuonPlotsByType<StandardMuonPlots>;
}

