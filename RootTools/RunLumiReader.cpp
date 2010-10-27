#include "RunLumiReader.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Toolbox/IOHelper.h"
#include "Toolbox/StringTools.h"

void readLumiFilter(const std::string json, std::map<run_id, std::set<std::pair<lumi_id, lumi_id> > > &lumifilter)
{
	using boost::property_tree::ptree;
	ptree pt;
	read_json(json, pt);
	for (ptree::const_iterator itRun = pt.begin(); itRun != pt.end(); ++itRun)
	{
		run_id run = parse<run_id>(itRun->first);
		for (ptree::const_iterator itLumiList = itRun->second.begin(); itLumiList != itRun->second.end(); ++itLumiList)
		{
			lumi_id lumi_low = 0, lumi_high = 0;
			for (ptree::const_iterator itLumiRange = itLumiList->second.begin(); itLumiRange != itLumiList->second.end(); ++itLumiRange)
			{
				if (lumi_low == 0)
					lumi_low = parse<lumi_id>(itLumiRange->second.data());
				else if (lumi_high == 0)
					lumi_high = parse<lumi_id>(itLumiRange->second.data());
			}
			lumifilter[run].insert(std::make_pair(lumi_low, lumi_high));
		}
	}
}

RunLumiSelector::RunLumiSelector(const std::string json, const run_id _passRunLow, const run_id _passRunHigh)
	: passRunLow(_passRunLow), passRunHigh(_passRunHigh)
{
	if (json != "")
		readLumiFilter(json, lumifilter);
}

RunLumiSelector::RunLumiSelector(const std::vector<std::string> &json, const run_id _passRunLow, const run_id _passRunHigh)
	: passRunLow(_passRunLow), passRunHigh(_passRunHigh)
{
	for (size_t i = 0; i < json.size(); ++i)
		readLumiFilter(json[i], lumifilter);
}

void RunLumiSelector::addJSONFile(const std::string json)
{
	readLumiFilter(json, lumifilter);
}

std::pair<run_id,lumi_id> RunLumiSelector::getMaxRunLumiPair()
{
	typedef std::set<std::pair<lumi_id, lumi_id> > lumirange;
	std::map<run_id,lumirange>::reverse_iterator iter = lumifilter.rbegin();
	return std::make_pair<run_id,lumi_id>(iter->first, iter->second.rbegin()->second);
}

void RunLumiSelector::printJSON(std::ostream &os)
{
	os << std::endl << "{";
	for (std::map<run_id, std::set<std::pair<lumi_id, lumi_id> > >::iterator it1 = lumifilter.begin(); it1 != lumifilter.end(); )
	{
		os << "\""<< (*it1).first << "\": [";
		for (std::set<std::pair<lumi_id, lumi_id> >::iterator it2 = (*it1).second.begin(); it2 != (*it1).second.end(); )
		{
			os << "[" << (*it2).first << "," << (*it2).second << "]";
			it2++;
			if (it2!=(*it1).second.end())
				os << ", ";
		}
		os << "]";
		it1++;
		if (it1!=lumifilter.end())
			os << ", ";
	}
	os << "}" << std::endl << std::endl;
}

const std::map<run_id, std::set<std::pair<lumi_id, lumi_id> > > & RunLumiSelector::getRunLumiMap(){
  return lumifilter;
}

std::ostream &operator<<(std::ostream &os, const std::pair<lumi_id, lumi_id> &p)
{
	return os << p.first << "-" << p.second;
}

std::ostream &operator<<(std::ostream &os, RunLumiSelector &m)
{
	os << "Accepted runs / lumis:" << std::endl << m.lumifilter << std::endl;
	if ((m.passRunLow > 0) || (m.passRunHigh > 0))
	{
		os << "All runs with ";
		if (m.passRunLow > 0)
			os << "run<=" << m.passRunLow << "";
		if ((m.passRunLow > 0) && (m.passRunHigh > 0))
			os << " and ";
		if (m.passRunHigh > 0)
			os << "run>=" << m.passRunHigh << "";
		os << " are automatically accepted" << std::endl;
	}
	return os;
}
