#include "StandardP4Plots.h"

KappaTools::StandardP4Plots::StandardP4Plots(TDirectory * tmpFile, TString tmpDirectory)
{
	getDirectory(tmpFile, tmpDirectory);

	pt 						= new TH1D("pt","p_{\\mathrm{T}}", 75, 0., 75.);
	pt_low 				= new TH1D("pt_low","p_{\\mathrm{T}}", 50, 0., 25.);
	pt_full 			= new TH1D("pt_full","p_{\\mathrm{T}}", 100, 0., 1000.);
	eta						= new TH1D("eta","#eta", 50, -5., 5.);
	eta_zoom			= new TH1D("eta_zoom","#eta", 50, -2.5, 2.5);
	phi						= new TH1D("phi","#phi", 50, -3.5, 3.5);
	mass					= new TH1D("mass","m", 75, 0., 250.);
	mass_low			= new TH1D("mass_low","m", 75, 0., 75.);
	mass_zwindow	= new TH1D("mass_zwindow","m", 70, 50., 130.);
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


template <typename PlottingClass, typename ObjectType1, typename ObjectType2>
KappaTools::PlotsByPt<PlottingClass, ObjectType1, ObjectType2>::PlotsByPt(std::vector<double> binning_, TDirectory * tmpFile, TString tmpDirectory) : binning(binning_), mode(FILL_EXCL)
{
	TDirectory * curDirectory = getDirectory(tmpFile, tmpDirectory);

	all = new PlottingClass(curDirectory, "all");
	underflow = new PlottingClass(curDirectory, "underflow");
	overflow = new PlottingClass(curDirectory, "overflow");

	for (unsigned int idx = 0; idx < binning.size(); idx++)
	{
		double pt_ = binning[idx];
		TString bname;
		if (pt_<100.)
			if (pt_<10.)
				bname = "pt_00";
			else
				bname = "pt_0";
		else
			bname = "pt_";
		bname+=pt_;
		plotsByBin.push_back(PlottingClass(curDirectory, bname.ReplaceAll(" ","")));
	}
}

template <typename PlottingClass, typename ObjectType1, typename ObjectType2>
void KappaTools::PlotsByPt<PlottingClass, ObjectType1, ObjectType2>::process(ObjectType1 * obj, KDataVertex * pv, double weight, ObjectType2 * obj2)
{
	if (!obj || !obj2)
		return;

	all->process(obj);

	if (binning.size()==0)
		return;

	double pt = obj2->p4.pt();

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

template <typename PlottingClass, typename ObjectType1, typename ObjectType2>
void KappaTools::PlotsByPt<PlottingClass, ObjectType1, ObjectType2>::final()
{
}

template <typename PlottingClass, typename ObjectType1, typename ObjectType2>
void KappaTools::PlotsByPt<PlottingClass, ObjectType1, ObjectType2>::setMode(char mode_)
{
	mode = mode_;
}


template <typename PlottingClass, typename ObjectType1, typename ObjectType2>
KappaTools::PlotsByEta<PlottingClass, ObjectType1, ObjectType2>::PlotsByEta(std::vector<double> binning_, TDirectory * tmpFile, TString tmpDirectory) : binning(binning_), mode(FILL_EXCL | FILL_ABS)
{
	TDirectory * curDirectory = getDirectory(tmpFile, tmpDirectory);

	all = new PlottingClass(curDirectory, "all");
	underflow = new PlottingClass(curDirectory, "underflow");
	overflow = new PlottingClass(curDirectory, "overflow");

	for (unsigned int idx = 0; idx < binning.size(); idx++)
	{
		double eta_ = binning[idx];
		TString bname = "eta_";
		bname+=eta_;
		plotsByBin.push_back(PlottingClass(curDirectory, bname.ReplaceAll(" ","")));
	}
}

template <typename PlottingClass, typename ObjectType1, typename ObjectType2>
void KappaTools::PlotsByEta<PlottingClass, ObjectType1, ObjectType2>::process(ObjectType1 * obj, KDataVertex * pv, double weight, ObjectType2 * obj2)
{
	if (!obj || !obj2)
		return;

	all->process(obj);

	if (binning.size()==0)
		return;

	double eta = obj2->p4.eta();

	if (eta < binning[0])
		underflow->process(obj);
	if (eta > binning[binning.size()-1])
		underflow->process(obj);

	for (unsigned int idx = 0; idx < binning.size(); idx++)
	{
		if (mode & FILL_ABS)
			eta = std::abs(eta);

		bool process = false;
		if (mode & FILL_EXCL)
			if (idx < binning.size()-1 && eta >= binning[idx] && eta < binning[idx+1])
				process = true;

		if (mode & FILL_INCL_UP)
			if (eta >= binning[idx])
				process = true;

		if (mode & FILL_INCL_DOWN)
			if (eta <= binning[idx])
				process = true;

		if (process)
			plotsByBin[idx].process(obj);
	}
}

template <typename PlottingClass, typename ObjectType1, typename ObjectType2>
void KappaTools::PlotsByEta<PlottingClass, ObjectType1, ObjectType2>::final()
{
}

template <typename PlottingClass, typename ObjectType1, typename ObjectType2>
void KappaTools::PlotsByEta<PlottingClass, ObjectType1, ObjectType2>::setMode(char mode_)
{
	mode = mode_;
}

template class KappaTools::PlotsByPt<KappaTools::ZmumuPlots<KDataJet, KDataMET>, KappaTools::ZmumuObjects<KDataJet, KDataMET>, KappaTools::ZmumuObjects<KDataJet, KDataMET> >;
template class KappaTools::PlotsByPt<KappaTools::ZmumuPlots<KDataPFJet, KDataMET>, KappaTools::ZmumuObjects<KDataPFJet, KDataMET>, KappaTools::ZmumuObjects<KDataPFJet, KDataMET> >;
template class KappaTools::PlotsByPt<KappaTools::ZmumuPlots<KDataPFJet, KDataPFMET>, KappaTools::ZmumuObjects<KDataPFJet, KDataPFMET>, KappaTools::ZmumuObjects<KDataPFJet, KDataPFMET> >;

template class KappaTools::PlotsByPt<KappaTools::ZmumuPlots<KDataJet, KDataMET>, KappaTools::ZmumuObjects<KDataJet, KDataMET>, KDataJet>;
template class KappaTools::PlotsByPt<KappaTools::ZmumuPlots<KDataPFJet, KDataMET>, KappaTools::ZmumuObjects<KDataPFJet, KDataMET>, KDataPFJet>;
template class KappaTools::PlotsByPt<KappaTools::ZmumuPlots<KDataPFJet, KDataPFMET>, KappaTools::ZmumuObjects<KDataPFJet, KDataPFMET>, KDataPFJet>;

template class KappaTools::PlotsByPt<KappaTools::ZmumuPlots<KDataJet, KDataMET>, KappaTools::ZmumuObjects<KDataJet, KDataMET>, KParton>;
template class KappaTools::PlotsByPt<KappaTools::ZmumuPlots<KDataPFJet, KDataMET>, KappaTools::ZmumuObjects<KDataPFJet, KDataMET>, KParton>;
template class KappaTools::PlotsByPt<KappaTools::ZmumuPlots<KDataPFJet, KDataPFMET>, KappaTools::ZmumuObjects<KDataPFJet, KDataPFMET>, KParton>;

template class KappaTools::PlotsByPt<KappaTools::MuonPlotsByType<KappaTools::StandardMuonPlots>, KDataMuon, KDataMuon >;
template class KappaTools::PlotsByEta<KappaTools::MuonPlotsByType<KappaTools::StandardMuonPlots>, KDataMuon, KDataMuon >;

