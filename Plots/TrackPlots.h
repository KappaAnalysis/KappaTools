/* Copyright (c) 2010 - All Rights Reserved
 *   Fred Stober <stober@cern.ch>
 *   Manuel Zeise <zeise@cern.ch>
 */

#ifndef KAPPA_TRACKPLOTS_H
#define KAPPA_TRACKPLOTS_H

#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "TDirectory.h"
#include "BasePlot.h"
#include "Kappa/DataFormats/interface/KMuon.h"

namespace KappaTools
{
	class StandardTrackPlots : public BasePlot
	{
		private:
			TH1D * ref_x;
			TH1D * ref_y;
			TH1D * ref_z;

			TH1D * ref_rho;

			TH1D * pt, * pt_low, * pt_full;
			TH1D * eta, * eta_zoom;
			TH1D * phi;

			TH1D * chi2;
			TH1D * ndof;
			TH1D * chi2norm;
			TH1D * chi2prob;

			TH1D * errPt;
			TH1D * errEta;
			TH1D * errPhi;
			TH1D * errDxy;
			TH1D * errDz;

			TH1D * nTrackerHits;
			TH1D * nValidMuonHits;
			TH1D * nPixelHits;
			TH1D * nStripHits;

			TH1D * quality;
		public:
			StandardTrackPlots(TDirectory * tmpFile_, TString tmpDirectory_, TString prefix="");

			// TDirectory
			void process(KDataTrack * track, KDataVertex * pv, double weight = 1.);
			void process(KDataTrack * track, KBeamSpot * bs, double weight = 1.);
			void process(KDataTrack * track, double weight = 1.);
			void final();
	};
}
#endif
