#ifndef PLOT_DATAJET_H
#define PLOT_DATAJET_H

#include "Plot_LV.h"

class Plot_DataJet : public Plot_LV
{
public:
	Plot_DataJet(PlotInterface pi, const std::string title, const bool correlation = false)
		: Plot_LV(pi, title, correlation)
	{
		emf = pi.book<TH1D>("emf", "electromagnetic fraction - " + title, bin_ratiom11);
		fHPD = pi.book<TH1D>("fHPD", "HPD fraction - " + title, bin_ratiom11);
		fRBX = pi.book<TH1D>("fRBX", "RBX fraction - " + title, bin_ratiom11);

		detectorEta = pi.book<TH1D>("deteta", "detector eta - " + title, bin_eta);

		n90 = pi.book<TH1D>("n90", "n90 - " + title, bin_jets);
		n90Hits = pi.book<TH1D>("n90Hits", "n90Hits - " + title, bin_jets);
		nConst = pi.book<TH1D>("nConst", "nConst - " + title, bin_jets);
		nTracksAtCalo = pi.book<TH1D>("nTracksAtCalo", "nTracksAtCalo - " + title, bin_jets);
		nTracksAtVertex = pi.book<TH1D>("nTracksAtVertex", "nTracksAtVertex - " + title, bin_jets);

		area = pi.book<TH1D>("area", "area - " + title, bin_jets);
		noiseHCAL = pi.book<TH1D>("noiseHCAL", "noiseHCAL - " + title, bin_jets);
	}

	inline void Fill(const KCaloJet &jet, const double weight)
	{
		Plot_LV::Fill(jet, weight);
		emf->Fill(jet.emf, weight);
		fHPD->Fill(jet.fHPD, weight);
		fRBX->Fill(jet.fRBX, weight);

		detectorEta->Fill(jet.detectorEta, weight);

		n90->Fill(jet.n90, weight);
		n90Hits->Fill(jet.n90Hits, weight);
		nConst->Fill(jet.nConst, weight);
		nTracksAtCalo->Fill(jet.nTracksAtCalo, weight);
		nTracksAtVertex->Fill(jet.nTracksAtVertex, weight);

		area->Fill(jet.area, weight);
		noiseHCAL->Fill(jet.noiseHCAL, weight);
	}

private:
	TH1D *emf, *area, *n90, *n90Hits;
	TH1D *noiseHCAL;
	TH1D *detectorEta;
	TH1D *fHPD;
	TH1D *fRBX;
	TH1D *nTracksAtCalo;
	TH1D *nTracksAtVertex;
	TH1D *nConst;
};

#endif
