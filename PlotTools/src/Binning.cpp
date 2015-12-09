#include "Binning.h"
#include <TAxis.h>
#include <assert.h>
#include <cmath>
#include <algorithm>

using namespace std;

MemoryPool<double*> Binning::binPool;

Binning::Binning()
{
	min = 0; max = 0; nbins = 0; res = 0; bins = 0;
}

Binning::Binning(const size_t _nbins, const double _min, const double _max, bool center)
{
	if (_nbins == 0)
	{
		std::cerr << _nbins << " " << _min << " " << _max << " " << center << std::endl;
		assert(_nbins != 0);
	}
	min = _min; max = _max; nbins = _nbins; res = (max - min) / nbins;
	if (center)
	{
		min -= res / 2.0;
		nbins++;
	}
	if (nbins > 0)
	{
		bins = new double[nbins + 1];
		binPool.AddObject(bins);
		for (size_t i = 0; i < nbins + 1; ++i)
			bins[i] = min + i * res;
	}
	else
		bins = 0;
}

Binning::Binning(const TAxis *axis)
{
	setup(axis->GetXbins()->GetSize(), axis->GetXbins()->GetArray());
}

Binning::Binning(const std::vector<double> _bins)
{
	std::vector<double> tmp = _bins;
	std::sort(tmp.begin(), tmp.end());
	setup(tmp.size(), tmp);
}

Binning::Binning(const size_t _nbins, const double *_bins)
{
	setup(nbins + 1, _bins);
}

Binning::Binning(const struct Binning _binning, const bool _mirror)
{
	if (_mirror)
	{
		min = -_binning.max; max = _binning.max; nbins = 2 * _binning.nbins; res = 0;
		bins = new double[nbins + 1];
		binPool.AddObject(bins);
		int j = 0;
		for (size_t i = _binning.nbins; i > 0; --i)
			bins[j++] = -_binning.bins[i];
		for (size_t i = 0; i < _binning.nbins + 1; ++i)
			bins[j++] = _binning.bins[i];
	}
}

std::ostream &operator<<(std::ostream &os, const Binning &b)
{
	for (size_t i = 0; i < b.nbins - 1; i++)
		os << "[" << b.bins[i] << "," << b.bins[i + 1] << ") - ";
	os << "[" << b.bins[b.nbins - 1] << "," << b.bins[b.nbins] << ")" << endl;
	return os;
}

LogBinning::LogBinning(const size_t nbins, const double min, double max, const int precision)
{
	std::vector<double> tmp(nbins + 1);
	const double step = std::pow(max / min, 1.0 / nbins);
	const double factor = std::pow(10.0, precision);
	tmp[0] = min;
	for (size_t i = 1; i < nbins + 1; ++i)
	{
		// Either multiplication of difference scales or avoid accumulating rounding errors
		if (max / min > 1e5)
			tmp[i] = std::floor(tmp[i - 1] * step * factor) / factor;
		else
			tmp[i] = std::floor(min * std::pow(step, (double)i) * factor) / factor;
		if (tmp[i] == tmp[i - 1])
			std::cerr << min << " " << max << " " << tmp[i] << " " << tmp[i - 1]
				<< " step: " << step << " factor: " << factor << std::endl;
	}
	assert(std::unique(tmp.begin(), tmp.end()) == tmp.end());
	setup(tmp.size(), tmp);
}

LogBinning::LogBinning(const size_t nbins, const double min, double max, const Binning forced, const int precision)
{
	std::vector<double> tmp;
	const double step = std::pow(max / min, 1.0 / nbins);
	const double factor = std::pow(10.0, precision);
	size_t fbin = 0;
	for (size_t i = 0; i < nbins + 1; ++i)
	{
		double edge = int(min * std::pow(step, (double)i) * factor) / factor;
		if ((edge > forced.bins[fbin]) && (fbin < forced.nbins))
			tmp.push_back(forced.bins[fbin++]);
		if (i == nbins)
			for (; fbin < forced.nbins; ++fbin)
				tmp.push_back(forced.bins[fbin]);
		tmp.push_back(edge);
	}
	tmp.resize(std::unique(tmp.begin(), tmp.end()) - tmp.begin());
	setup(tmp.size(), tmp);
}

Variable::Variable(const Binning _binning, const string _name, const bool _log)
	: binning(_binning), name(_name), log(_log)
{
}

Variable::Variable(const TAxis *axis, const bool _log)
	: binning(axis), name(axis->GetTitle()), log(_log)
{
}
