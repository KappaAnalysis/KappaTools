#ifndef KAPPA_ADVANCEDPLOTS_H
#define KAPPA_ADVANCEDPLOTS_H

#include "TH1D.h"
#include "TDirectory.h"
#include "BasePlot.h"
#include "Kappa/DataFormats/interface/KLorentzVector.h"

#include "../Objects/Zmumu.h"
#include "MuonPlots.h"
#include "ZmumuPlots.h"

namespace KappaTools
{
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

