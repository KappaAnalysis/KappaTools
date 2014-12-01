/* Copyright (c) 2010 - All Rights Reserved
 *   Fred Stober <stober@cern.ch>
 *   Manuel Zeise <zeise@cern.ch>
 */

#ifndef KAPPA_STANDARDPLOTS_H
#define KAPPA_STANDARDPLOTS_H

#include "TH1D.h"
#include "TH2D.h"
#include "TDirectory.h"
#include "BasePlot.h"
#include "Kappa/DataFormats/interface/KRoot.h"

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

			void process(RMDLV p4, double weight = 1.0);
			void final();
	};
	
	class TriggerP4Plots : public StandardP4Plots
	{
		public:
		TH1D *pt_binned;
		TH1D *eta_binned, *eta_regions;
		TH2D * pt_eta;

		TriggerP4Plots(TDirectory * tmpFile, TString tmpDirectory);
		void process(RMDLV p4, double weight = 1.0);
		void process(RMFLV p4, double weight = 1.0);
		void final();
	};
}
#endif

