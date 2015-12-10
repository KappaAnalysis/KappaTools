#include "../interface/BookPlots.h"

namespace RawPlotInterface
{

template<>
TH1D *book(const std::string name, const TH1D *ref)
{
	return book<TH1D>(name, ref->GetTitle(), Variable(ref->GetXaxis()));
}

template<>
TH2D *book(const std::string name, const TH2D *ref)
{
	return book<TH2D>(name, ref->GetTitle(), Variable(ref->GetXaxis()), Variable(ref->GetYaxis()));
}

template<>
TProfile *book(const std::string name, const TProfile *ref)
{
	return book<TProfile>(name, ref->GetTitle(), Variable(ref->GetXaxis()));
}

TH2D *bookTransposed(const std::string name, const TH2D *ref)
{
	return book<TH2D>(name, ref->GetTitle(), Variable(ref->GetYaxis()), Variable(ref->GetXaxis()));
}

template<>
TNtuple *book(const std::string name, const std::string varlist)
{
	TNtuple *tuple = new TNtuple(name.c_str(), name.c_str(), varlist.c_str());
	tuple->SetDirectory(0);
	return tuple;
}

}
