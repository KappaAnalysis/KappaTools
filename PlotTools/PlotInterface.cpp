#include "PlotInterface.h"
#include <TFile.h>

std::map<TFile*, int> PlotInterface::refCount;
//std::map<TFile*, std::vector<PlotHolderBase*> > PlotInterface::cbList;

PlotInterface::PlotInterface(const std::string filename, const FileOpenType _fot)
{
	fot = _fot;
	if (fot == readonly)
		plotfile = new TFile(filename.c_str(), "READ");
	else if (fot == reset)
		plotfile = new TFile(filename.c_str(), "RECREATE");
	else
		plotfile = new TFile(filename.c_str(), "UPDATE");
	root = plotfile;
	refCount[plotfile]++;
}

PlotInterface::PlotInterface(const PlotInterface &pi)
	: plotfile(pi.plotfile), root(pi.root)
{
	refCount[plotfile]++;
}

PlotInterface::PlotInterface(TFile *pf, TDirectory *r, FileOpenType t)
	: plotfile(pf), root(r), fot(t)
{
	refCount[plotfile]++;
}

PlotInterface::~PlotInterface()
{
	refCount[plotfile]--;
	plotfile->Flush();
	if (refCount[plotfile] == 0)
	{
		std::cout << "Writing plot file..." << std::endl;
		if (fot != readonly)
		{
			// Call holder callbacks
//			for (size_t i = 0; i < PlotInterface::cbList[plotfile].size(); ++i)
//				PlotInterface::cbList[plotfile][i]->Write();
			plotfile->Write();
		}
		delete plotfile;
		std::cout << "Plot file closed!" << std::endl;
	}
}

PlotInterface PlotInterface::dir(std::string name)
{
	// Handle absolute paths
	if (name.find_first_of("/") == 0)
		return PlotInterface(plotfile, plotfile, fot).dir(KappaTools::strip(name, "/"));
	std::string _dir;
	if (splitDirFromName(name, _dir))
		return dir(_dir).dir(name);
	ROOTGuard guard;
	if (root->Get(name.c_str()) == 0)
		root->mkdir(name.c_str());
	root->cd(name.c_str());
	return PlotInterface(plotfile, gDirectory, fot);
}

bool PlotInterface::splitDirFromName(std::string &name, std::string &dir)
{
	bool absolute = (name.find_first_of("/") == 0);
	name = KappaTools::strip(name, "/");
	if (KappaTools::in('/', name))
	{
		std::vector<std::string> tmp = KappaTools::split(name, "/", 1);
		dir = absolute ? "/" + tmp[0] : tmp[0];
		name = tmp[1];
		return true;
	}
	return false;
}

template<>
TGraph *PlotInterface::insert(TGraph *plot)
{
	root->Append(plot);
	return plot;
}
