#ifndef KStandardPlots_h
#define KStandardPlots_h

#include "TH1D.h"
#include "TDirectory.h"
#include "BasePlot.h"
#include "DataFormats/interface/KLorentzVector.h"

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
}
#endif

