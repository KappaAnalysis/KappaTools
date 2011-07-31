#ifndef KAPPA_RUNLUMIREADER_H
#define KAPPA_RUNLUMIREADER_H

#include <set>
#include <Kappa/DataFormats/interface/Kappa.h>

void readLumiFilter(const std::string json, std::map<run_id, std::set<std::pair<lumi_id, lumi_id> > > &lumifilter);

class RunLumiSelector
{
public:
	RunLumiSelector(const std::string json = "", const run_id _passRunLow = 1, const run_id _passRunHigh = 0);
	RunLumiSelector(const std::vector<std::string> &json, const run_id _passRunLow = 1, const run_id _passRunHigh = 0);
	void addJSONFile(const std::string json = "");
	inline bool accept(const run_id run, const lumi_id lumi) const
	{
		if (((passRunLow > 0) && (run <= passRunLow)) ||
			((passRunHigh > 0) && (run >= passRunHigh)))
			return true;
		typedef std::set<std::pair<lumi_id, lumi_id> > lumirange;
		std::map<run_id, lumirange>::const_iterator itRun = lumifilter.find(run);
		if (itRun == lumifilter.end())
			return false;
		const lumirange &lumis = itRun->second;
		for (lumirange::const_iterator itLumis = lumis.begin(); itLumis != lumis.end(); ++itLumis)
			if (lumi < itLumis->first)
				return false;
			else
				if ((lumi >= itLumis->first) && (lumi <= itLumis->second))
					return true;
		return false;
	}
	std::pair<run_id, run_id> getBoundaries()
	{
		run_id min=std::numeric_limits<run_id>::max(), max = std::numeric_limits<run_id>::min();
		if (lumifilter.size()==0)
			return std::make_pair(max, min);
		for (std::map<run_id, std::set<std::pair<lumi_id, lumi_id> > >::const_iterator it = lumifilter.begin(); it != lumifilter.end(); ++it)
		{
			if (it->first < min)
				min = it->first;
			if (it->first > max)
				max = it->first;
		}
		return std::make_pair(min, max);
	}
	std::pair<run_id, lumi_id> getMaxRunLumiPair();

	void printJSON(std::ostream &os = std::cout);
	const std::map<run_id, std::set<std::pair<lumi_id, lumi_id> > > & getRunLumiMap();
	friend std::ostream &operator<<(std::ostream &os, RunLumiSelector &m);
private:
	run_id passRunLow, passRunHigh;
	std::map<run_id, std::set<std::pair<lumi_id, lumi_id> > > lumifilter;
};

std::ostream &operator<<(std::ostream &os, RunLumiSelector &m);

#endif
