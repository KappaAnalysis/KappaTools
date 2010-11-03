#ifndef KAPPA_STANDARDPLOTS_H
#define KAPPA_STANDARDPLOTS_H

#include "TH1D.h"
#include "TDirectory.h"
#include "BasePlot.h"
#include "DataFormats/interface/KLorentzVector.h"

#include "Objects/Zmumu.h"
#include "MuonPlots.h"
#include "ZmumuPlots.h"

namespace KappaTools
{
	class StandardP4Plots : public BasePlot
	{
		private:
		public:
			TH1D * pt, * pt_low, * pt_full;
			TH1D * eta, * eta_zoom;

			TH1D * phi;
			TH1D * mass, * mass_low, * mass_zwindow;
			TH2D * eta_zoom_phi;

			StandardP4Plots(TDirectory * tmpFile, TString tmpDirectory);

			void process(RMLV p4, double weight = 1.0);
			void final();
	};
	
	class TriggerP4Plots : public StandardP4Plots
	{
		public:
		TH1D *pt_binned;
		TH1D *eta_binned, *eta_regions;
		TH2D * pt_eta;

		TriggerP4Plots(TDirectory * tmpFile, TString tmpDirectory);
		void process(RMLV p4, double weight = 1.0);
		void process(RMDataLV p4, double weight = 1.0);
		void final();
	};

	// ObjectType1 -- Object to plot
	// ObjectType2 -- Object for binning
	template <typename PlottingClass, typename ObjectType1, typename ObjectType2>
	class PlotsByPt : public BasePlot
	{
		private:
			PlottingClass * all, * underflow, * overflow;
			std::vector<PlottingClass> plotsByBin;
			std::vector<double> binning;
			int mode;
		public:
			//PlotsByPt(TDirectory * tmpFile, TString tmpDirectory="");
			PlotsByPt(std::vector<double> binning_, TDirectory * tmpFile, TString tmpDirectory="");
			void process(ObjectType1 * obj, KDataVertex * pv = 0, double weight = 1., ObjectType2 * obj2 = 0);
			void final();

			void setMode(char mode_);

			static const char FILL_EXCL = 1;
			static const char FILL_INCL_UP = 2;
			static const char FILL_INCL_DOWN = 4;

			static const char FILL_ABS = 8;
	};

	// ObjectType1 -- Object to plot
	// ObjectType2 -- Object for binning
	template <typename PlottingClass, typename ObjectType1, typename ObjectType2>
	class PlotsByEta : public BasePlot
	{
		private:
			PlottingClass * all, * underflow, * overflow;
			std::vector<PlottingClass> plotsByBin;
			std::vector<double> binning;
			int mode;
		public:
			PlotsByEta(std::vector<double> binning_, TDirectory * tmpFile, TString tmpDirectory="");
			void process(ObjectType1 * obj, KDataVertex * pv = 0, double weight = 1., ObjectType2 * obj2 = 0);
			void final();

			void setMode(char mode_);

			static const char FILL_EXCL = 1;
			static const char FILL_INCL_UP = 2;
			static const char FILL_INCL_DOWN = 4;

			static const char FILL_ABS = 8;
	};
}
#endif

