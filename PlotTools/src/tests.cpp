#include <TFile.h>
#include <iostream>
#include "PlotInterface.h"
#include "Plot_Run.h"
#include "../RootTools/libKRootTools.h"

using namespace std;

void TestBook(PlotInterface pf, std::string name)
{
	TH1D *h = pf.book<TH1D>(name, bin_eta);
	h->FillRandom("gaus");
}

void printObjList(TDirectory *dir)
{
	const std::vector<TObject*> list = getSecond<std::map<std::string, TObject*>, TObject*>(GetDirObjectsMap(dir));
	for (size_t i = 0; i < list.size(); ++i)
		cout << list[i] << " " << list[i]->GetName() << " " << list[i]->ClassName() << endl;
}

int main(int, char **argv)
{
//	TFile input("input.root");

	TFile out1("output1.root", "RECREATE");
	PlotInterface pf1("output2.root", PlotInterface::reset);
	PlotInterface pfx("output3.root", PlotInterface::readonly);

/*
	Binning(const size_t _nbins, const double _min, const double _max, bool center = false);
	Binning(const TAxis *axis);
	Binning(const size_t _nbins, const double *_bins);
	Binning(const struct Binning _binning, const bool _mirror);
*/
	std::vector<double> tbinv;
	tbinv.push_back(1);
	tbinv.push_back(1.2);
	tbinv.push_back(1.6);
	tbinv.push_back(2.1);
	Binning tbin(tbinv);
	cout << tbin << endl;

	cout << LogBinning(2, 10, 1000) << endl;
	cout << LogBinning(4, 10, 1000) << endl;
	cout << LogBinning(10, 10, 1000) << endl;

	cout << LogBinning(4, 10, 1000, -1) << endl;
	cout << LogBinning(4, 10, 1000, 0) << endl;
	cout << LogBinning(4, 10, 1000, 1) << endl;
	cout << LogBinning(4, 10, 1000, 2) << endl;
	cout << LogBinning(10, 10, 1000, 2) << endl;

	cout << Binning(5, 200, 700) << endl;
	cout << LogBinning(10, 10, 1000) << endl;
	cout << LogBinning(10, 10, 1000, Binning(5, 300, 800)) << endl;

	TestBook(pf1, "test_ra");
	TestBook(pf1, "test_rb");

	PlotInterface pf2 = pf1.dir("level1a");
	TestBook(pf2, "test_1a_a");
	TestBook(pf2, "test_1a_b");

	TNtuple *tuple = pf1.book<TNtuple>("tuple", "x");
	for (int i = 0; i < 100; ++i)
		tuple->Fill(1 / (i*i + 1));

	PlotInterface pf3 = pf1.dir("level1b");
	TestBook(pf3, "test_1b_a");

	PlotInterface pf4 = pf1.dir("level1a");
	TestBook(pf4, "test_1a_c");

	PlotInterface pf5 = pf2.dir("level2a");
	TestBook(pf5, "test_1a_2a_a");

	TestBook(pf1.dir("level1a"), "test_1a_d");
	TestBook(pf1.dir("level1b"), "test_1a_e");

	TestBook(pf1.dir("level1a").dir("level2a"), "test_1a_2a_b");
	TestBook(pf1.dir("level1b").dir("level2b"), "test_1b_2b_a");

	TestBook(pf1, "level1b/level2b/test_1b_2b_b");
	TestBook(pf1, "/level1b/level2b/test_1b_2b_c");
	TestBook(pf5, "/level1b/level2b/test_1b_2b_d");

	cout << pf1.get<TH1D>("test_ra") << endl;
	cout << pf2.get<TH1D>("test_1a_a") << endl;
	cout << pf5.get<TH1D>("test_1a_2a_b") << endl;
	cout << pf1.dir("level1b").dir("level2b").get<TH1D>("test_1b_2b_a") << endl;
	cout << pf1.get<TH1D>("level1b/level2b/test_1b_2b_a") << endl;
	cout << pf4.get<TH1D>("/level1b/level2b/test_1b_2b_a") << endl;
	cout << pf1.getAll<TH1D>() << endl;
//	cout << pf1.dirs() << endl;

	cout << "====" << endl;
	printObjList(pf1.root);
	cout << "====" << endl;
	TestBook(pfx, "HALLOWELT");
	printObjList(pfx.root);
	cout << pfx.dirs() << endl;

	Plot_Run *pr = new Plot_Run(pf1, "Run1", bin_eta);
	Plot_Run *pr1 = new Plot_Run(pf1, "Run2", bin_eta);
	Plot_Run::SetLS(1, 2);
	pr->Fill(1);
	pr->Fill(3);
	pr1->Fill(11);
	pr1->Fill(13);
	Plot_Run::SetLS(3, 2);
	pr->Fill(2);
	pr->Fill(3);
	pr1->Fill(2);
	pr1->Fill(3);

	std::cout << pf1.getAll<TH1D>(true) << std::endl;
	Plot_Run::flushAll();
	std::cout << pf1.getAll<TH1D>(true) << std::endl;

//	for (int bin = 0; bin <= h_out->GetXaxis()->GetNbins() + 1; ++bin)
//		cout << h_out->GetBinContent(bin) << "[" << h_out->GetBinError(bin) << "] ";
//	cout << endl;

	return 0;
}
