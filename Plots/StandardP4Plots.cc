#include "StandardP4Plots.h"

KappaTools::TriggerP4Plots::TriggerP4Plots(TDirectory * tmpFile, TString tmpDirectory) : StandardP4Plots::StandardP4Plots(tmpFile, tmpDirectory)
{
	double pt_binning[11] = { 0,5,9,12,15,20,30,40,60,100 };
	//double pt_binning[16] = { 0,5,6,7,8,9,10,11,13,15,20,25,40,60,100 };
	//double eta_binning[17] = { -2.4, -2.1, -1.8, -1.5, -1.2, -0.9, -0.6, -0.3, 0, 0.3, 0.6, 0.9, 1.2, 1.5, 1.8, 2.1, 2.4};
	double eta_binning[21] = { -2.4, -2.1, -1.85, -1.6, -1.4, -1.2, -1.05, -0.9, -0.6, -0.3, 0, 0.3, 0.6, 0.9, 1.05, 1.2, 1.4, 1.6, 1.85, 2.1, 2.4};
	double eta_regions_binning[8] = { -2.4, -2.1, -1.2, -0.9, 0.9, 1.2, 2.1, 2.4};

	pt_binned		= new TH1D("pt_binned","p_{\\mathrm{T}}", 9, pt_binning);
	pt_binned->Sumw2();
	
	eta_binned		= new TH1D("eta_binned","#eta", 20, eta_binning);
	eta_binned->Sumw2();

	eta_regions		= new TH1D("eta_regions","#eta", 7, eta_regions_binning);
	eta_regions->Sumw2();
	
	pt_eta = new TH2D("pt_eta", "#pt vs. #eta", 7, eta_regions_binning, 9, pt_binning);
	pt_eta->Sumw2();
}

void KappaTools::TriggerP4Plots::process(RMDataLV p4, double weight)
{
	process((RMLV) p4, weight);
}
void KappaTools::TriggerP4Plots::process(RMLV p4, double weight)
{
	pt_binned->Fill(p4.pt(), weight);
	eta_binned->Fill(p4.eta(), weight);
	eta_regions->Fill(p4.eta(), weight);
	pt_eta->Fill(p4.eta(), p4.pt(), weight);
	StandardP4Plots::process(p4, weight);
}

void KappaTools::TriggerP4Plots::final()
{
	StandardP4Plots::final();
}

KappaTools::StandardP4Plots::StandardP4Plots(TDirectory * tmpFile, TString tmpDirectory)
{
	getDirectory(tmpFile, tmpDirectory);

	pt 					= new TH1D("pt","p_{\\mathrm{T}}", 75, 0., 75.);
	pt->Sumw2();
	pt_low 				= new TH1D("pt_low","p_{\\mathrm{T}}", 50, 0., 25.);
	pt_low->Sumw2();

	pt_full 			= new TH1D("pt_full","p_{\\mathrm{T}}", 100, 0., 1000.);
	pt_full->Sumw2();
	eta					= new TH1D("eta","#eta", 50, -5., 5.);
	eta->Sumw2();

	eta_zoom			= new TH1D("eta_zoom","#eta", 50, -2.5, 2.5);
	eta_zoom->Sumw2();
	phi					= new TH1D("phi","#phi", 50, -3.5, 3.5);
	phi->Sumw2();
	mass				= new TH1D("mass","m", 75, 0., 250.);
	mass->Sumw2();
	mass_low			= new TH1D("mass_low","m", 75, 0., 75.);
	mass_low->Sumw2();
	mass_zwindow		= new TH1D("mass_zwindow","m", 70, 50., 130.);
	mass_zwindow->Sumw2();
	eta_zoom_phi		= new TH2D("eta_zoom_phi", "#eta vs. #phi", 50, -2.5, 2.5, 50, -3.5, 3.5);
	eta_zoom_phi->Sumw2();
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
	eta_zoom_phi->Fill(p4.eta(), p4.phi(), weight);
}

void KappaTools::StandardP4Plots::final()
{
}
