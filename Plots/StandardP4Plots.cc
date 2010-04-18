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


template <typename PlottingClass, typename ObjectType>
KappaTools::PlotsByPt<PlottingClass, ObjectType>::PlotsByPt(std::vector<double> binning_, TDirectory * tmpFile, TString tmpDirectory, TString tmpSubDirectory) : binning(binning_), mode(FILL_EXCL)
{
	TDirectory * curDirectory = getDirectory(tmpFile, tmpDirectory, tmpSubDirectory);

	all = new PlottingClass(curDirectory, "all", "");
	underflow = new PlottingClass(curDirectory, "underflow", "");
	overflow = new PlottingClass(curDirectory, "overflow", "");

	for (unsigned int idx = 0; idx < binning.size(); idx++)
	{
		double pt_ = binning[idx];
		TString bname = (pt_<10. ? "pt_0" : "pt_");
		bname+=pt_;
		plotsByBin.push_back(PlottingClass(curDirectory, bname, ""));
	}
}

template <typename PlottingClass, typename ObjectType>
void KappaTools::PlotsByPt<PlottingClass, ObjectType>::process(ObjectType * obj, KDataVertex * pv, double weight)
{
	if (!obj)
		return;

	all->process(obj);

	if (binning.size()==0)
		return;

	double pt = obj->p4.pt();

	if (pt < binning[0])
		underflow->process(obj);
	if (pt > binning[binning.size()-1])
		underflow->process(obj);

	for (unsigned int idx = 0; idx < binning.size(); idx++)
	{
		if (mode & FILL_ABS)
			pt = std::abs(pt);

		bool process = false;
		if (mode & FILL_EXCL)
			if (idx < binning.size()-1 && pt >= binning[idx] && pt < binning[idx+1])
				process = true;

		if (mode & FILL_INCL_UP)
			if (pt >= binning[idx])
				process = true;

		if (mode & FILL_INCL_DOWN)
			if (pt <= binning[idx])
				process = true;

		if (process)
			plotsByBin[idx].process(obj);
	}
}

template <typename PlottingClass, typename ObjectType>
void KappaTools::PlotsByPt<PlottingClass, ObjectType>::final()
{
}

template <typename PlottingClass, typename ObjectType>
void KappaTools::PlotsByPt<PlottingClass, ObjectType>::setMode(char mode_)
{
	mode = mode_;
}


template <typename PlottingClass, typename ObjectType>
KappaTools::PlotsByEta<PlottingClass, ObjectType>::PlotsByEta(std::vector<double> binning_, TDirectory * tmpFile, TString tmpDirectory, TString tmpSubDirectory) : binning(binning_), mode(FILL_EXCL | FILL_ABS)
{
	TDirectory * curDirectory = getDirectory(tmpFile, tmpDirectory, tmpSubDirectory);

	all = new PlottingClass(curDirectory, "all", "");
	underflow = new PlottingClass(curDirectory, "underflow", "");
	overflow = new PlottingClass(curDirectory, "overflow", "");

	for (unsigned int idx = 0; idx < binning.size(); idx++)
	{
		double eta_ = binning[idx];
		TString bname = "eta_";
		bname+=eta_;
		plotsByBin.push_back(PlottingClass(curDirectory, bname, ""));
	}
}

template <typename PlottingClass, typename ObjectType>
void KappaTools::PlotsByEta<PlottingClass, ObjectType>::process(ObjectType * obj, KDataVertex * pv, double weight)
{
	if (!obj)
		return;

	all->process(obj);

	if (binning.size()==0)
		return;

	double pt = obj->p4.eta();

	if (pt < binning[0])
		underflow->process(obj);
	if (pt > binning[binning.size()-1])
		underflow->process(obj);

	for (unsigned int idx = 0; idx < binning.size(); idx++)
	{
		if (mode & FILL_ABS)
			pt = std::abs(pt);

		bool process = false;
		if (mode & FILL_EXCL)
			if (idx < binning.size()-1 && pt >= binning[idx] && pt < binning[idx+1])
				process = true;

		if (mode & FILL_INCL_UP)
			if (pt >= binning[idx])
				process = true;

		if (mode & FILL_INCL_DOWN)
			if (pt <= binning[idx])
				process = true;

		if (process)
			plotsByBin[idx].process(obj);
	}
}

template <typename PlottingClass, typename ObjectType>
void KappaTools::PlotsByEta<PlottingClass, ObjectType>::final()
{
}

template <typename PlottingClass, typename ObjectType>
void KappaTools::PlotsByEta<PlottingClass, ObjectType>::setMode(char mode_)
{
	mode = mode_;
}

template class KappaTools::PlotsByPt<KappaTools::MuonPlotsByType<KappaTools::StandardMuonPlots>, KDataMuon >;
template class KappaTools::PlotsByEta<KappaTools::MuonPlotsByType<KappaTools::StandardMuonPlots>, KDataMuon >;

