#ifndef KStandardPlots_h
#define KStandardPlots_h

#include "TH1D.h"
#include "TDirectory.h"
#include "BasePlot.h"
#include "DataFormats/interface/KLorentzVector.h"

#include "MuonPlots.h"

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

			StandardP4Plots(TDirectory * tmpFile, TString tmpDirectory, TString tmpSubDirectory);

			void process(RMLV p4, double weight = 1.0);
			void final();
	};

	template <typename PlottingClass, typename ObjectType>
	class PlotsByPt : public BasePlot
	{
		private:
			PlottingClass * all, * underflow, * overflow;
			std::vector<PlottingClass> plotsByBin;
			std::vector<double> binning;
			int mode;
		public:
			//PlotsByPt(TDirectory * tmpFile, TString tmpDirectory, TString tmpSubDirectory="");
			PlotsByPt(std::vector<double> binning_, TDirectory * tmpFile, TString tmpDirectory, TString tmpSubDirectory="");
			void process(ObjectType * obj, KDataVertex * pv = 0, double weight = 1.);
			void final();

			void setMode(char mode_);

			static const char FILL_EXCL = 1;
			static const char FILL_INCL_UP = 2;
			static const char FILL_INCL_DOWN = 4;

			static const char FILL_ABS = 8;
	};

	template <typename PlottingClass, typename ObjectType>
	class PlotsByEta : public BasePlot
	{
		private:
			PlottingClass * all, * underflow, * overflow;
			std::vector<PlottingClass> plotsByBin;
			std::vector<double> binning;
			int mode;
		public:
			PlotsByEta(std::vector<double> binning_, TDirectory * tmpFile, TString tmpDirectory, TString tmpSubDirectory="");
			void process(ObjectType * obj, KDataVertex * pv = 0, double weight = 1.);
			void final();

			void setMode(char mode_);

			static const char FILL_EXCL = 1;
			static const char FILL_INCL_UP = 2;
			static const char FILL_INCL_DOWN = 4;

			static const char FILL_ABS = 8;
	};
}
#endif

