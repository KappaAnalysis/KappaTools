#include "TrackPlots.h"

namespace KappaTools
{
	StandardTrackPlots::StandardTrackPlots(TDirectory * tmpFile_, TString tmpDirectory_, TString prefix)
	{
		getDirectory(tmpFile_, tmpDirectory_);

		pt 						= new TH1D("pt","p_{\\mathrm{T}}", 75, 0., 75.);
		pt_low 				= new TH1D("pt_low","p_{\\mathrm{T}}", 50, 0., 25.);
		pt_full 			= new TH1D("pt_full","p_{\\mathrm{T}}", 100, 0., 1000.);
		eta						= new TH1D("eta","#eta", 50, -5., 5.);
		eta_zoom			= new TH1D("eta_zoom","#eta", 50, -2.5, 2.5);
		phi						= new TH1D("phi","#phi", 50, -3.5, 3.5);

		ref_x					= new TH1D("ref_x","x_{\\mathrm{ref.}}", 100, -3., 3.);
		ref_y					= new TH1D("ref_y","y_{\\mathrm{ref.}}", 100, -3., 3.);
		ref_z					= new TH1D("ref_z","z_{\\mathrm{ref.}}", 100, -15., 15.);
		ref_rho				= new TH1D("ref_rho","#rho_{\\mathrm{ref.}}", 100, -15., 15.);

		chi2					= new TH1D("chi2","#chi^{2}", 50, 0., 50.);
		ndof					= new TH1D("ndof","\\mathrm{ndof}", 50, 0., 50.);
		chi2norm			= new TH1D("chi2norm","#chi^{2} / \\mathrm{ndof}", 50, 0., 25.);
		chi2prob			= new TH1D("chi2prob","\\mathrm{prob}(#chi^{2})", 50, 0., 1.);

		errPt	= new TH1D("errPt","errPt", 100, 0., 0.25);
		errEta	= new TH1D("errEta","errEta", 100, 0., 0.025);
		errPhi	= new TH1D("errPhi","errPhi", 100, 0., 0.025);
		errDxy	= new TH1D("errDxy","errDxy", 100, 0., 0.75);
		errDz	= new TH1D("errDz","errDz", 100, 0., 2.5);

		nTrackerHits	= new TH1D("nTrackerHits","\\mathrm{hits\\,\\,in\\,\\,tracker}", 50, 0., 50.);
		nValidMuonHits= new TH1D("nValidMuonHits","\\mathrm{hits\\,\\,in\\,\\,muon}", 75, 0., 75.);
		nPixelHits		= new TH1D("nPixelHits","\\mathrm{hits\\,\\,in\\,\\,pixel}", 15, 0., 15.);
		nStripHits		= new TH1D("nStripHits","\\mathrm{hits\\,\\,in\\,\\,strip}", 30, 0., 30.);

		quality				= new TH1D("quality", "\\mathrm{track\\,\\,quality}", 16, 0., 16.);
	}

	void StandardTrackPlots::process(KDataTrack * track, KDataVertex * pv, double weight)
	{
		if (!track || track->nDOF == 0)
			return;

		pt->Fill(track->p4.pt(), weight);
		pt_low->Fill(track->p4.pt(), weight);
		pt_full->Fill(track->p4.pt(), weight);
		eta->Fill(track->p4.eta(), weight);
		eta_zoom->Fill(track->p4.eta(), weight);
		phi->Fill(track->p4.phi(), weight);

		ref_x->Fill(track->ref.x(), weight);
		ref_y->Fill(track->ref.y(), weight);
		ref_z->Fill(track->ref.z(), weight);
		ref_rho->Fill(track->ref.rho(), weight);

		chi2->Fill(track->chi2, weight);
		ndof->Fill(track->nDOF, weight);
		chi2norm->Fill(track->chi2/track->nDOF, weight);
		chi2prob->Fill(TMath::Prob(track->chi2, static_cast<int>(track->nDOF)), weight);

		errPt->Fill(track->errPt);
		errEta->Fill(track->errEta);
		errPhi->Fill(track->errPhi);
		errDxy->Fill(track->errDxy);
		errDz->Fill(track->errDz);

		nTrackerHits->Fill(track->nValidPixelHits+track->nValidStripHits);
		nValidMuonHits->Fill(track->nValidMuonHits);

		nPixelHits->Fill(track->nValidPixelHits);
		nStripHits->Fill(track->nValidStripHits);

		quality->Fill(track->quality);
	}

	void StandardTrackPlots::final()
	{
	}
}
