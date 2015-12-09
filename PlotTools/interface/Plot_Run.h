#ifndef RUNWRAPPER_H
#define RUNWRAPPER_H

#include "PlotInterface.h"
#include <Kappa/DataFormats/interface/Kappa.h>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/weighted_mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/weighted_variance.hpp>
#include <boost/accumulators/statistics/skewness.hpp>
#include <boost/accumulators/statistics/weighted_skewness.hpp>
#include <boost/accumulators/statistics/kurtosis.hpp>
#include <boost/accumulators/statistics/weighted_kurtosis.hpp>

typedef boost::accumulators::accumulator_set<double, boost::accumulators::features<
	boost::accumulators::tag::count,
	boost::accumulators::tag::mean,
	boost::accumulators::tag::variance,
	boost::accumulators::tag::skewness,
	boost::accumulators::tag::kurtosis>, double> Plot_Run_Accumulator;
typedef std::map<run_id, Plot_Run_Accumulator> Plot_Run_Accumulator_Map;

struct Plot_Run_Holder
{
	Plot_Run_Holder(PlotInterface _pi, std::string _name)
		: pi(_pi), name(_name)
	{
	}

	PlotInterface pi;
	std::string name;
	Plot_Run_Accumulator_Map infoMap;

	void flush()
	{
		if (infoMap.size() > 0)
		{
			PlotInterface piRun = pi.dir(name + "_byrun");
			Binning run_bins(infoMap.size(), 0, infoMap.size());
			TH1D *plot_run = piRun.book<TH1D>("run", run_bins);
			TH1D *plot_count = piRun.book<TH1D>("count", run_bins);
			TH1D *plot_mean = piRun.book<TH1D>("mean", run_bins);
			TH1D *plot_vari = piRun.book<TH1D>("vari", run_bins);
			TH1D *plot_skew = piRun.book<TH1D>("skew", run_bins);
			TH1D *plot_kurt = piRun.book<TH1D>("kurt", run_bins);
			int n = 1;
			for (Plot_Run_Accumulator_Map::const_iterator it = infoMap.begin(); it != infoMap.end(); ++it, ++n)
			{
				plot_run->SetBinContent(n, it->first);
				plot_count->SetBinContent(n, boost::accumulators::count(it->second));
				plot_mean->SetBinContent(n, boost::accumulators::mean(it->second));
				plot_vari->SetBinContent(n, boost::accumulators::variance(it->second));
				plot_skew->SetBinContent(n, boost::accumulators::skewness(it->second));
				plot_kurt->SetBinContent(n, boost::accumulators::kurtosis(it->second));
			}
		}
	}
};

class Plot_Run
{
public:
	Plot_Run(PlotInterface _pi, const std::string _name, const Binning bin)
		: plot(_pi.book<TH1D>(_name, _name, bin))
	{
		Plot_Run::instances.push_back(Plot_Run_Holder(_pi, _name));
		accMap = &(Plot_Run::instances.back().infoMap);
	}

	Plot_Run(PlotInterface _pi, const std::string _name, const std::string _title, const Binning bin)
		: plot(_pi.book<TH1D>(_name, _title, bin))
	{
		Plot_Run::instances.push_back(Plot_Run_Holder(_pi, _name));
		accMap = &(Plot_Run::instances.back().infoMap);
	}

	static void flushAll()
	{
		for (std::list<Plot_Run_Holder>::iterator it = Plot_Run::instances.begin(); it != Plot_Run::instances.end(); ++it)
			it->flush();
		Plot_Run::instances.clear();
	}

	inline void Fill(const double value, const double w = 1)
	{
		plot->Fill(value, w);
		if (Plot_Run::useLumi)
			(*accMap)[lumi](value, boost::accumulators::weight = w);
		else
			(*accMap)[run](value, boost::accumulators::weight = w);
	}

	static void SetLS(const run_id _run, const lumi_id _lumi)
	{
		run = _run;
		lumi = _lumi;
	}

	static void SetMode(const bool _useLumi)
	{
		useLumi = _useLumi;
	}

private:
	Plot_Run_Accumulator_Map *accMap;
	static std::list<Plot_Run_Holder> instances;

	TH1D *plot;
	static run_id run;
	static lumi_id lumi;
	static bool useLumi;
};

#endif
