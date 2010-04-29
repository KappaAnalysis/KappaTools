#ifndef KAPPA_VERTEXPLOTS_H
#define KAPPA_VERTEXPLOTS_H

#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "TDirectory.h"
#include "BasePlot.h"
#include "DataFormats/interface/KBasic.h"

namespace KappaTools
{
	class StandardVertexPlots : public BasePlot
	{
		private:

			TH1D * pos_xy, * pos_z, * pos_rho;

			TH1D * isFake;
			TH1D * nTracks;

			TH1D * chi2;
			TH1D * ndof;
			TH1D * chi2norm;
			TH1D * chi2prob;

		public:
			StandardVertexPlots(TDirectory * tmpFile, TString tmpDirectory, TString tmpSubDirectory="");

			// TDirectory
			void process(KDataVertex * pv, double weight = 1.);
			void final();
	};
}
#endif

