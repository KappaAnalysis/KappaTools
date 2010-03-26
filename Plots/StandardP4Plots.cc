#include "StandardP4Plots.h"

KappaTools::StandardP4Plots::StandardP4Plots(TDirectory * tmpFile, TString tmpDirectory, TString tmpSubDirectory)
{
	getDirectory(tmpFile, tmpDirectory, tmpSubDirectory);

	pt 						= new TH1D("pt","p_{T}", 75, 0., 75.);
	pt_low 				= new TH1D("pt_low","p_{T}", 50, 0., 25.);
	pt_full 			= new TH1D("pt_full","p_{T}", 100, 0., 1000.);
	eta						= new TH1D("eta","#eta", 50, -5., 5.);
	eta_zoom			= new TH1D("eta_zoom","#eta", 50, -2.5, 2.5);
	phi						= new TH1D("phi","#phi", 50, -3.5, 3.5);
	mass					= new TH1D("mass","mass", 75, 0., 250.);
	mass_low			= new TH1D("mass_low","mass", 75, 0., 75.);
	mass_zwindow	= new TH1D("mass_zwindow","mass", 70, 50., 130.);
}

void KappaTools::StandardP4Plots::process(RMLV p4, double weight)
{
	pt->Fill(p4.pt(), weight);
	pt_low->Fill(p4.pt(), weight);
	pt_full->Fill(p4.pt(), weight);
	eta->Fill(p4.eta(), weight);
	eta_zoom->Fill(p4.eta(), weight);
	phi->Fill(p4.phi(), weight);
	mass->Fill(p4.mass(), weight);
	mass_low->Fill(p4.mass(), weight);
	mass_zwindow->Fill(p4.mass(), weight);
}

void KappaTools::StandardP4Plots::final()
{
}

