#ifndef KAPPA_MUONPLOTS_H
#define KAPPA_MUONPLOTS_H

#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "TDirectory.h"
#include "BasePlot.h"
#include "TrackPlots.h"

#include "Kappa/DataFormats/interface/KMuon.h"
/*
#include "TFile.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TString.h"
#include <Math/VectorUtil.h>

//#include <Math/LorentzVector.h>
//#include <Math/PtEtaPhiM4D.h>
#include "../../MTAObjects/interface/MTAMuon.h"
#include "../../MTAObjects/interface/MTAVertex.h"
#include "../../MTAObjects/interface/MTAGenParticle.h"
#include <cmath>
#include <stdlib.h>
*/

namespace KappaTools
{
	class StandardMuonPlots : public BasePlot
	{
		private:
			TH1D * muon_pt, * muon_pt_low, * muon_pt_fine, * muon_pt_medium;
			TH1D * muon_eta, * muon_eta_zoom, * muon_phi;
			TH2D * muon_eta_phi, * muon_eta_zoom_phi;

			TH1D * muon_ecalIso03;
			TH1D * muon_hcalIso03;
			TH1D * muon_trackIso03;
			TH1D * muon_sumPtIso03;
			TH1D * muon_relCombIso03;

			TH1D * muon_pfIso04;
			TH1D * muon_relCombPFIso04;
			TH1D * muon_ecalIso05;
			TH1D * muon_hcalIso05;
			TH1D * muon_trackIso05;
			TH1D * muon_sumPtIso05;

			TH1D * muon_numberOfChambers;

			TH1D * vertex_zdist;

			TH1D * IP, * IP_zoom;
			TH1D * IPSig;
			TH2D * IPvsIPSig;

			TH1D * IP_abs, * IP_zoom_abs;
			TH1D * IPSig_abs;
			TH2D * IPvsIPSig_abs;

			TH1D * muon_type;

			TH1D * caloComp;
			TH1D * segComp;

			KappaTools::StandardTrackPlots * track;
			KappaTools::StandardTrackPlots * innerTrack;
			KappaTools::StandardTrackPlots * globalTrack;

			/*
				MTAPoint vertex;
				double vertex_chi2;
				double vertex_ndof;
				double vertex_chi2prob;

				-- bool isTrackerMuon;
				-- bool isCaloMuon;
				-- bool isStandAloneMuon;
				-- bool isGlobalMuon;

				-- float hcalIso03;
				-- float ecalIso03;
				-- float trackIso03;

				unsigned int isGoodMuon;

				float caloComp, segComp;

				-- int numberOfChambers;
				-- int trackHits;
			*/
		public:
			StandardMuonPlots(TDirectory * tmpFile, TString tmpDirectory, TString prefix="");

			// TDirectory
			void process(KDataMuon * muon, KDataVertex * pv, double weight = 1.);
			void process(KDataMuon * muon, KDataBeamSpot * bs, double weight = 1.);
			void process(KDataMuon * muon, double weight = 1.);
			void final();
	};

	template <typename T>
	class MuonPlotsByType : public BasePlot
	{
		private:
			T * allMuons;
			T * trackerMuons;
			T * standaloneMuons;
			T * caloMuons;
			T * globalMuons;
			T * realGlobalMuons;
		public:
			MuonPlotsByType(TDirectory * tmpFile, TString tmpDirectory);
			void process(KDataMuon * muon, KDataVertex * pv = 0, double weight = 1.);
			void final();
	};
}
#endif

