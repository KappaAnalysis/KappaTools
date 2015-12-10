#ifndef PLOT_BINNED_H
#define PLOT_BINNED_H

#include "PlotInterface.h"

struct BinnedHolderBase
{
	BinnedHolderBase(Variable _var) : var(_var)
	{
	}

	inline std::string getName(int idx = -1)
	{
		if (idx < 0)
			return std::string(var.name) + "_" + str(var.binning.bins[var.binning.nbins]) + "_inf";
		return std::string(var.name) + "_" + str(var.binning.bins[idx]) + "_" + str(var.binning.bins[idx+1]);
	}

	size_t getIdx(double value)
	{
		// TODO: binary search for Variable
		const Binning &bins = var.binning;
		for (size_t i = 0; i < bins.nbins; ++i)
			if (bins.bins[i + 1] > value)
				return i;
		return bins.nbins;
	}

	Variable var;
};

template<typename T>
struct BinnedHolder : public BinnedHolderBase
{
	BinnedHolder(PlotInterface pi, Variable _bins) : BinnedHolderBase(_bins)
	{
		for (size_t i = 0; i < var.binning.nbins; ++i)
			subplots.push_back(T(pi.dir(getName(i))));
		subplots.push_back(T(pi.dir(getName())));
	}

	template<typename P1>
	BinnedHolder(PlotInterface pi, Variable _bins, P1 p1) : BinnedHolderBase(_bins)
	{
		for (size_t i = 0; i < var.binning.nbins; ++i)
			subplots.push_back(T(pi.dir(getName(i)), p1));
		subplots.push_back(T(pi.dir(getName()), p1));
	}

	template<typename P1, typename P2>
	BinnedHolder(PlotInterface pi, Variable _bins, P1 p1, P2 p2) : BinnedHolderBase(_bins)
	{
		for (size_t i = 0; i < var.binning.nbins; ++i)
			subplots.push_back(T(pi.dir(getName(i)), p1, p2));
		subplots.push_back(T(pi.dir(getName()), p1, p2));
	}

	template<typename P1, typename P2, typename P3>
	BinnedHolder(PlotInterface pi, Variable _bins, P1 p1, P2 p2, P3 p3) : BinnedHolderBase(_bins)
	{
		for (size_t i = 0; i < var.binning.nbins; ++i)
			subplots.push_back(T(pi.dir(getName(i)), p1, p2, p3));
		subplots.push_back(T(pi.dir(getName()), p1, p2, p3));
	}

	template<typename P1, typename P2, typename P3, typename P4>
	BinnedHolder(PlotInterface pi, Variable _bins, P1 p1, P2 p2, P3 p3, P4 p4) : BinnedHolderBase(_bins)
	{
		for (size_t i = 0; i < var.binning.nbins; ++i)
			subplots.push_back(T(pi.dir(getName(i)), p1, p2, p3, p4));
		subplots.push_back(T(pi.dir(getName()), p1, p2, p3, p4));
	}

	T &Get(double value)
	{
		return subplots[getIdx(value)];
	}

	std::vector<T> subplots;
};

template<>
struct BinnedHolder<TH1D> : public BinnedHolderBase
{
	BinnedHolder(PlotInterface pi, Variable _bins, std::string _name, Variable _bins1) : BinnedHolderBase(_bins)
	{
		for (size_t i = 0; i < var.binning.nbins; ++i)
			subplots.push_back(pi.dir(getName(i)).book<TH1D>(_name, _bins1));
		subplots.push_back(pi.dir(getName()).book<TH1D>(_name, _bins1));
	}

	TH1D &Get(double value)
	{
		return *subplots[getIdx(value)];
	}

	std::vector<TH1D*> subplots;
};

template<>
struct BinnedHolder<TH2D> : public BinnedHolderBase
{
	BinnedHolder(PlotInterface pi, Variable _bins, std::string _name, Variable _bins1, Variable _bins2) : BinnedHolderBase(_bins)
	{
		for (size_t i = 0; i < var.binning.nbins; ++i)
			subplots.push_back(pi.dir(getName(i)).book<TH2D>(_name, _bins1, _bins2));
		subplots.push_back(pi.dir(getName()).book<TH2D>(_name, _bins1, _bins2));
	}

	TH2D &Get(double value)
	{
		return *subplots[getIdx(value)];
	}

	std::vector<TH2D*> subplots;
};

template<>
struct BinnedHolder<TProfile> : public BinnedHolderBase
{
	BinnedHolder(PlotInterface pi, Variable _bins, std::string _name, Variable _bins1) : BinnedHolderBase(_bins)
	{
		for (size_t i = 0; i < var.binning.nbins; ++i)
			subplots.push_back(pi.dir(getName(i)).book<TProfile>(_name, _bins1));
		subplots.push_back(pi.dir(getName()).book<TProfile>(_name, _bins1));
	}

	TProfile &Get(double value)
	{
		return *subplots[getIdx(value)];
	}

	std::vector<TProfile*> subplots;
};

#endif
