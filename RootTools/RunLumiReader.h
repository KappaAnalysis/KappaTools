#include <DataFormats/src/classes.h>
#include <boost/property_tree/ptree.hpp>

void readLumiFilter(const std::string json, std::map<run_id, std::vector<std::pair<lumi_id, lumi_id> > > &lumifilter);

class RunLumiSelector
{
public:
	RunLumiSelector(const run_id _passRun = 1, const std::string json = "");
	inline bool accept(const run_id run, const lumi_id lumi) const
	{
		if (run <= passRun)
			return true;
		std::map<run_id, std::vector<std::pair<lumi_id, lumi_id> > >::const_iterator itRun = lumifilter.find(run);
		if (itRun == lumifilter.end())
			return false;
		const std::vector<std::pair<lumi_id, lumi_id> > &lumis = itRun->second;
		for (std::vector<std::pair<lumi_id, lumi_id> >::const_iterator itLumis = lumis.begin(); itLumis != lumis.end(); ++itLumis)
			if (lumi < itLumis->first)
				return false;
			else
				if ((lumi >= itLumis->first) && (lumi <= itLumis->second))
					return true;
		return false;
	}

	friend std::ostream &operator<<(std::ostream &os, RunLumiSelector &m);
private:
	run_id passRun;
	std::map<run_id, std::vector<std::pair<lumi_id, lumi_id> > > lumifilter;
};

std::ostream &operator<<(std::ostream &os, RunLumiSelector &m);
