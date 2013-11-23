#ifndef PLOT_DATAPFJET_H
#define PLOT_DATAPFJET_H

#include "Plot_LV.h"

class Plot_DataPFJet : public Plot_LV
{
public:
	Plot_DataPFJet(PlotInterface pi, const std::string title, const bool correlation = false, const Binning ptBinning = bin_logpt_default)
		: Plot_LV(pi, title, correlation, ptBinning)
	{
		nEMF = pi.book<TH1D>("nEMF", "neutral electromagnetic fraction - " + title, bin_ratiom11);
		cEMF = pi.book<TH1D>("cEMF", "charged electromagnetic fraction - " + title, bin_ratiom11);

		nHadF = pi.book<TH1D>("nHadF", "neutral hadronic fraction - " + title, bin_ratiom11);
		cHadF = pi.book<TH1D>("cHadF", "charged hadronic fraction - " + title, bin_ratiom11);

		nCharged = pi.book<TH1D>("nCharged", "nCharged - " + title, bin_jets);
		nConst = pi.book<TH1D>("nConst", "nConst - " + title, bin_jets);

		area = pi.book<TH1D>("area", "area - " + title, bin_area);
	}

	inline void Fill(const KDataPFJet &jet, const double weight)
	{
		Plot_LV::Fill(jet, weight);
		nEMF->Fill(jet.neutralEMFraction, weight);
		cEMF->Fill(jet.chargedEMFraction, weight);

		nHadF->Fill(jet.neutralHadFraction, weight);
		cHadF->Fill(jet.chargedHadFraction, weight);

		nCharged->Fill(jet.nCharged, weight);
		nConst->Fill(jet.nConst, weight);

		area->Fill(jet.area, weight);
	}

private:
	TH1D *area, *nCharged, *nConst;
	TH1D *nEMF, *cEMF;
	TH1D *nHadF, *cHadF;
};

#endif
