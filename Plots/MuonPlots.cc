#include "MuonPlots.h"

namespace KappaTools
{
	StandardMuonPlots::StandardMuonPlots(TDirectory * tmpFile_, TString tmpDirectory_, TString prefix)
	{
		TDirectory * tmpDirectory = getDirectory(tmpFile_, tmpDirectory_);
		double muon_pt_medium_binning[16] = { 0,5,6,7,8,9,10,11,13,16,20,25,40,60,100 };
		
		muon_pt 				= new TH1D(prefix+"pt","p_{\\mathrm{T}}", 75, 0., 150.);
		muon_pt->Sumw2();
		muon_pt_fine			= new TH1D(prefix+"pt_fine","p_{\\mathrm{T}}", 200, 0., 200.);
		muon_pt_fine->Sumw2();
		muon_pt_low		 		= new TH1D(prefix+"pt_low","p_{\\mathrm{T}}", 50, 0., 25.);
		muon_pt_low->Sumw2();
		muon_pt_medium			= new TH1D(prefix+"pt_medium","p_{\\mathrm{T}}", 14, muon_pt_medium_binning);
		muon_pt_medium->Sumw2();
		muon_eta 				= new TH1D(prefix+"eta","#eta", 50, -5., 5.);
		muon_eta->Sumw2();
		muon_eta_zoom			= new TH1D(prefix+"eta_zoom","#eta", 50, -2.5, 2.5);
		muon_eta_zoom->Sumw2();
		muon_phi				= new TH1D(prefix+"phi","#phi", 50, -3.5, 3.5);
		muon_phi->Sumw2();
		muon_eta_phi			= new TH2D(prefix+"eta_phi", "#eta vs. #phi", 50, -5., 5., 50, -3.5, 3.5);
		muon_eta_phi->Sumw2();
		muon_eta_zoom_phi		= new TH2D(prefix+"eta_zoom_phi", "#eta vs. #phi", 50, -2.5, 2.5, 50, -3.5, 3.5);
		muon_eta_zoom_phi->Sumw2();

		muon_ecalIso03			= new TH1D(prefix+"ecalIso03","\\mathrm{iso}_{\\mathrm{ecal}}(0.3)", 50, 0, 10.);
		muon_ecalIso03->Sumw2();
		muon_hcalIso03			= new TH1D(prefix+"hcalIso03","\\mathrm{iso}_{\\mathrm{hcal}}(0.3)", 50, 0, 10.);
		muon_hcalIso03->Sumw2();
		muon_trackIso03			= new TH1D(prefix+"trackIso03","\\mathrm{iso}_{\\mathrm{trk.}}(0.3)", 50, 0, 10.);
		muon_trackIso03->Sumw2();
		muon_sumPtIso03			= new TH1D(prefix+"sumPtIso03","\\mathrm{iso}_{\\mathrm{trk.}}(0.3)", 50, 0, 10.);
		muon_sumPtIso03->Sumw2();
		muon_relCombIso03		= new TH1D(prefix+"relCombIso03","\\mathrm{iso}_{\\mathrm{rel.}}(0.3)", 60, 0., 0.5);
		muon_relCombIso03->Sumw2();
		muon_relCombPFIso04		= new TH1D(prefix+"relCombPFIso04", "\\mathrm{iso}_{\\mathrm{rel.\\,pf.}}(0.4)", 60, 0., 0.5);
		muon_relCombPFIso04->Sumw2();

		muon_pfIso04			= new TH1D(prefix+"pfIso04","\\mathrm{iso}_{\\mathrm{pf}}(0.4)", 50, 0, 10.);
		muon_pfIso04->Sumw2();

		muon_ecalIso05			= new TH1D(prefix+"ecalIso05","\\mathrm{iso}_{\\mathrm{ecal}}(0.5)", 50, 0, 10.);
		muon_ecalIso05->Sumw2();
		muon_hcalIso05			= new TH1D(prefix+"hcalIso05","\\mathrm{iso}_{\\mathrm{hcal}}(0.5)", 50, 0, 10.);
		muon_hcalIso05->Sumw2();
		muon_trackIso05			= new TH1D(prefix+"trackIso05","\\mathrm{iso}_{\\mathrm{trk.}}(0.5)", 50, 0, 10.0);
		muon_trackIso05->Sumw2();
		muon_sumPtIso05			= new TH1D(prefix+"sumPtIso05","\\mathrm{iso}_{\\mathrm{trk.}}(0.5)", 50, 0, 10.);
		muon_sumPtIso05->Sumw2();

		muon_type				= new TH1D(prefix+"type","\\mathrm{muon\\,\\,type:\\,\\,exists,\\,\\,tracker,\\,\\,calo,\\,\\,sta,\\,\\,global}", 10, 0, 5);
		muon_type->Sumw2();

		muon_numberOfChambers	= new TH1D(prefix+"numberOfChambers","number of muon chambers", 20, -0.5, 19.5);
		muon_numberOfChambers->Sumw2();

		vertex_zdist			= new TH1D(prefix+"vertex_zdist","d(\\mathrm{PV},\\mu)", 50, 0., 1.);
		vertex_zdist->Sumw2();

		IP						= new TH1D(prefix+"IP","\\mathrm{IP}", 100, -0.05, 0.05);
		IP->Sumw2();
		IP_zoom					= new TH1D(prefix+"IP_zoom","\\mathrm{IP}", 100, -0.01, 0.01);
		IP_zoom->Sumw2();
		IPSig					= new TH1D(prefix+"IPSig","\\mathrm{IP}_\\mathrm{signif.}", 100, -10, 10);
		IPSig->Sumw2();
		IPvsIPSig				= new TH2D(prefix+"IPvsIPSig","\\mathrm{IP\\,\\,vs\\,\\,IP}_\\mathrm{signif.}", 100, -0.05, 0.05, 100, -10, 10);
		IPvsIPSig->Sumw2();

		IP_abs					= new TH1D(prefix+"IP_abs","\\mathrm{IP}", 100, 0., 0.05);
		IP_abs->Sumw2();
		IP_zoom_abs				= new TH1D(prefix+"IP_zoom_abs","\\mathrm{IP}", 100, 0., 0.01);
		IP_zoom_abs->Sumw2();
		IPSig_abs				= new TH1D(prefix+"IPSig_abs","\\mathrm{IP}_\\mathrm{signif.}", 100, 0., 10.);
		IPSig_abs->Sumw2();
		IPvsIPSig_abs			= new TH2D(prefix+"IPvsIPSig_abs","\\mathrm{IP\\,\\,vs\\,\\,IP}_\\mathrm{signif.}", 100, 0., 0.05, 100, 0., 10.);
		IPvsIPSig_abs->Sumw2();

		caloComp	= new TH1D(prefix+"caloComp","\\mathrm{calo\\,\\,compatibility}", 100, 0., 1.);
		caloComp->Sumw2();
		segComp		= new TH1D(prefix+"segComp","\\mathrm{segment\\,\\,compatibility}", 100, 0., 1.);
		segComp->Sumw2();

		track = new KappaTools::StandardTrackPlots(tmpDirectory, prefix+"track");
		innerTrack = new KappaTools::StandardTrackPlots(tmpDirectory, prefix+"innerTrack");
		globalTrack = new KappaTools::StandardTrackPlots(tmpDirectory, prefix+"globalTrack");

		tmpDirectory->cd();
	}
	void StandardMuonPlots::process(KDataMuon * muon, KDataVertex * pv, double weight)
	{
		if (!muon)
			return;

		process(muon, weight);

		if (pv)
		{
			IP->Fill(muon->track.getIP(pv,0), weight);
			IP_zoom->Fill(muon->track.getIP(pv,0), weight);
			IPSig->Fill(muon->track.getIP(pv,2), weight);
			IPvsIPSig->Fill(muon->track.getIP(pv,0),muon->track.getIP(pv,2), weight);
			vertex_zdist->Fill(std::abs(muon->track.ref.z()-pv->position.z()));

			IP_abs->Fill(std::abs(muon->track.getIP(pv,0)), weight);
			IP_zoom_abs->Fill(std::abs(muon->track.getIP(pv,0)), weight);
			IPSig_abs->Fill(std::abs(muon->track.getIP(pv,2)), weight);
			IPvsIPSig_abs->Fill(std::abs(muon->track.getIP(pv,0)),std::abs(muon->track.getIP(pv,2)), weight);
		}

		track->process(&muon->track, pv, weight);
		innerTrack->process(&muon->innerTrack, pv, weight);
		globalTrack->process(&muon->globalTrack, pv, weight);
	}
	void StandardMuonPlots::process(KDataMuon * muon, KDataBeamSpot * bs, double weight)
	{
		if (!muon)
			return;

		process(muon, weight);

		if (bs)
		{
			IP->Fill(muon->track.getIP(bs,0), weight);
			IP_zoom->Fill(muon->track.getIP(bs,0), weight);
			IPSig->Fill(muon->track.getIP(bs,2), weight);
			IPvsIPSig->Fill(muon->track.getIP(bs,0),muon->track.getIP(bs,2), weight);
			vertex_zdist->Fill(std::abs(muon->track.ref.z()-bs->position.z()));

			IP_abs->Fill(std::abs(muon->track.getIP(bs,0)), weight);
			IP_zoom_abs->Fill(std::abs(muon->track.getIP(bs,0)), weight);
			IPSig_abs->Fill(std::abs(muon->track.getIP(bs,2)), weight);
			IPvsIPSig_abs->Fill(std::abs(muon->track.getIP(bs,0)),std::abs(muon->track.getIP(bs,2)), weight);
		}

		track->process(&muon->track, bs, weight);
		innerTrack->process(&muon->innerTrack, bs, weight);
		globalTrack->process(&muon->globalTrack, bs, weight);
	}
	void StandardMuonPlots::process(KDataMuon * muon, double weight)
	{
		if (!muon)
			return;

		muon_pt->Fill(muon->p4.pt(), weight);
		muon_pt_low->Fill(muon->p4.pt(), weight);
		muon_pt_fine->Fill(muon->p4.pt(), weight);
		muon_pt_medium->Fill(muon->p4.pt(), weight);
		muon_eta->Fill(muon->p4.eta(), weight);
		muon_eta_zoom->Fill(muon->p4.eta(), weight);
		muon_phi->Fill(muon->p4.phi(), weight);
		muon_eta_phi->Fill(muon->p4.eta(), muon->p4.phi(), weight);
		muon_eta_zoom_phi->Fill(muon->p4.eta(), muon->p4.phi(), weight);

		muon_ecalIso03->Fill(muon->ecalIso03, weight);
		muon_hcalIso03->Fill(muon->hcalIso03, weight);
		muon_trackIso03->Fill(muon->trackIso03, weight);
		muon_sumPtIso03->Fill(muon->sumPtIso03, weight);
		muon_relCombIso03->Fill((muon->ecalIso03+muon->hcalIso03+muon->sumPtIso03)/muon->p4.pt(), weight);
		muon_relCombPFIso04->Fill((muon->pfIso04)/muon->p4.pt(), weight);

		muon_pfIso04->Fill(muon->pfIso04, weight);

		muon_ecalIso05->Fill(muon->ecalIso05, weight);
		muon_hcalIso05->Fill(muon->hcalIso05, weight);
		muon_trackIso05->Fill(muon->trackIso05, weight);
		muon_sumPtIso05->Fill(muon->sumPtIso05, weight);

		muon_numberOfChambers->Fill(muon->numberOfChambers, weight);

		muon_type->Fill(0., weight);
		if (muon->isTrackerMuon())
			muon_type->Fill(1., weight);
		if (muon->isCaloMuon())
			muon_type->Fill(2., weight);
		if (muon->isStandAloneMuon())
			muon_type->Fill(3., weight);
		if (muon->isGlobalMuon())
			muon_type->Fill(4., weight);

		caloComp->Fill(muon->caloComp, weight);
		segComp->Fill(muon->segComp, weight);
	}
	void StandardMuonPlots::final()
	{
	}

	template <typename T>
	MuonPlotsByType<T>::MuonPlotsByType(TDirectory * tmpFile, TString tmpDirectory)
	{
		TDirectory * curDirectory = getDirectory(tmpFile, tmpDirectory);

		allMuons = new KappaTools::StandardMuonPlots(curDirectory, "all", "");
		trackerMuons = new KappaTools::StandardMuonPlots(curDirectory, "tracker", "");
		caloMuons = new KappaTools::StandardMuonPlots(curDirectory, "calo", "");
		standaloneMuons = new KappaTools::StandardMuonPlots(curDirectory, "standalone", "");
		globalMuons = new KappaTools::StandardMuonPlots(curDirectory, "global", "");
		realGlobalMuons = new KappaTools::StandardMuonPlots(curDirectory, "realglobal", "");
	}

	template <typename T>
	void MuonPlotsByType<T>::process(KDataMuon * muon, KDataVertex * pv, double weight)
	{
		if (!muon)
			return;

		allMuons->process(muon, pv, weight);
		if (muon->isTrackerMuon())
			trackerMuons->process(muon, pv, weight);
		if (muon->isCaloMuon())
			caloMuons->process(muon, pv, weight);
		if (muon->isStandAloneMuon())
			standaloneMuons->process(muon, pv, weight);
		if (muon->isGlobalMuon())
			globalMuons->process(muon, pv, weight);
		if (muon->isTrackerMuon() && muon->isGlobalMuon())
			realGlobalMuons->process(muon, pv, weight);
	}

	template <typename T>
	void MuonPlotsByType<T>::final()
	{
	}

	template class MuonPlotsByType<StandardMuonPlots>;
}

