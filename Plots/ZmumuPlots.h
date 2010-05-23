#ifndef KAPPA_ZMUMUPLOTS_H
#define KAPPA_ZMUMUPLOTS_H

#include "TH1D.h"
#include "TH2D.h"
#include "TDirectory.h"
#include "BasePlot.h"
#include "MuonPlots.h"
#include "JetPlots.h"
#include "TNtuple.h"

#include "DataFormats/interface/KMuon.h"
#include "../Objects/Zmumu.h"
#include "Math/GenVector/VectorUtil.h"
namespace KappaTools
{
	template <typename JetType, typename METType>
	class ZmumuPlots : public BasePlot
	{
		private:
			TH1D * Z_mass, * Z_mass_low, * Z_mass_zoom;
			TH1D * Z_phi, * Z_eta, * Z_pt, * Z_pt_full;
			TH1D * muons_dR, * muons_dPhi;

			TH1D * zjet_dR, * zjet_dPhi, * zjet_dPhi_zoom;
			TH1D * jet_response;

			StandardMuonPlots * muons_plots;
			StandardMuonPlots * muon1_plots;
			StandardMuonPlots * muon2_plots;

			StandardJetPlots<JetType> * jet_plots;
		public:
			ZmumuPlots(TDirectory * tmpFile, TString tmpDirectory="");

			// TDirectory
			void process(KappaTools::ZmumuObjects<JetType, METType> * zmumu, double weight = 1.0);
			void final();
	};

	template <typename ZmumuType>
	class ZmumuNtuple : public BasePlot
	{
		private:
			TNtuple * ntuple;
		public:
			ZmumuNtuple(TDirectory * tmpFile, TString tmpDirectory="");
			void process(ZmumuType * zmumu, double weight = 1.0);
			void final();
	};
}
#endif
