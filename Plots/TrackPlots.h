#ifndef KTrackPlots_h
#define KTrackPlots_h

#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "TDirectory.h"
#include "BasePlot.h"
#include "DataFormats/interface/KMuon.h"

namespace KappaTools
{
	class StandardTrackPlots : public BasePlot
	{
		private:
			TH1D * ref_x;
			TH1D * ref_y;
			TH1D * ref_z;

			TH1D * pt, * pt_low, * pt_full;
			TH1D * eta, * eta_zoom;
			TH1D * phi;
			
			TH1D * charge;
			TH1D * chi2;
			TH1D * ndof;
			TH1D * chi2norm;
			TH1D * chi2prob;

			TH1D * errPt;
			TH1D * errEta;
			TH1D * errPhi;
			TH1D * errDxy;
			TH1D * errDz;

			TH1D * nPixelHits;
			TH1D * nStripHits;
			
			TH1D * quality;
		public:
			StandardTrackPlots(TDirectory * tmpFile, TString tmpDirectory, TString tmpSubDirectory="");

			// TDirectory
			void process(KDataTrack * track, KDataVertex * pv = 0, double weight = 1.);
			void final();
	};
}
#endif

