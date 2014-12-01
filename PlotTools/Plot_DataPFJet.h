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
		nConstituents = pi.book<TH1D>("nConstituents", "nConstituents - " + title, bin_jets);

		area = pi.book<TH1D>("area", "area - " + title, bin_area);
	}

	inline void Fill(const KBasicJet &jet, const double weight)
	{
		Plot_LV::Fill(jet, weight);
		nEMF->Fill(jet.photonFraction, weight);
		cEMF->Fill(jet.electronFraction, weight);

		nHadF->Fill(jet.neutralHadronFraction, weight);
		cHadF->Fill(jet.chargedHadronFraction, weight);

		nCharged->Fill(jet.nCharged, weight);
		nConstituents->Fill(jet.nConstituents, weight);

		area->Fill(jet.area, weight);
	}

private:
	TH1D *area, *nCharged, *nConstituents;
	TH1D *nEMF, *cEMF;
	TH1D *nHadF, *cHadF;
};

#endif
