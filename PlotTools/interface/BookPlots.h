#ifndef BOOKPLOTS_H
#define BOOKPLOTS_H

#include <string>
#include <TNtuple.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TProfile.h>

#include "Binning.h"
#include "../../Toolbox/interface/String.h"

namespace RawPlotInterface
{

template<typename T>
T *setupBooking(T *plot, std::string labelX = "", std::string labelY = "")
{
	plot->SetDirectory(0);
	if (plot->GetSumw2()->GetSize() == 0)
		plot->Sumw2();
	if (labelX != "")
		plot->SetXTitle(_S(labelX));
	if (labelY != "")
		plot->SetYTitle(_S(labelY));
	return plot;
}

template<typename T>
T *book(const std::string name, const std::string title, const Variable bin)
{
	return setupBooking(new T(_S(name), _S(title), bin.binning.nbins, bin.binning.bins), bin.name);
}

template<typename T>
T *book(const std::string name, const std::string param);
template<>
TNtuple *book(const std::string name, const std::string varlist);

template<typename T>
T *book(const std::string name, const Variable bin)
{
	return book<T>(name, name, bin);
}

template<typename T>
T *book(const std::string name, const std::string title, const Variable bin, const std::string opt)
{
	return setupBooking(new T(_S(name), _S(title), bin.binning.nbins, bin.binning.bins, _S(opt)), bin.name);
}

template<typename T>
T *book(const std::string name, const Variable bin, const std::string opt)
{
	return book<T>(name, name, bin, opt);
}

template<typename T>
T *book(const std::string name, const std::string title, const Variable bin1, const Variable bin2)
{
	T *result = setupBooking(new T(_S(name), _S(title),
		bin1.binning.nbins, bin1.binning.bins,
		bin2.binning.nbins, bin2.binning.bins),
		bin1.name, bin2.name);
	return result;
}

template<typename T>
T *book(const std::string name, const Variable bin1, const Variable bin2)
{
	return book<T>(name, name, bin1, bin2);
}

template<typename T>
T *book(const std::string name, const T *ref);

template<>
TH1D *book(const std::string name, const TH1D *ref);

template<>
TH2D *book(const std::string name, const TH2D *ref);

TH2D *bookTransposed(const std::string name, const TH2D *ref);

template<>
TProfile *book(const std::string name, const TProfile *ref);

template<typename T>
T *clone(const std::string name, const T *ref)
{
	T *hist = static_cast<T*>(ref->Clone(_S(name)));
	return setupBooking(hist, ref->GetXaxis()->GetTitle(), ref->GetYaxis()->GetTitle());
}

}

#endif
