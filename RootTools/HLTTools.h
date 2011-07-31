#ifndef KAPPA_HLTTOOLS_H
#define KAPPA_HLTTOOLS_H

#include <Kappa/DataFormats/interface/Kappa.h>
#include <boost/regex.hpp>

class HLTTools
{
private:
	KLumiMetadata * lumiMetadata;
public:
	HLTTools(KLumiMetadata * lumiMetadata = 0)
	{
		this->lumiMetadata = lumiMetadata;
	}
	void setLumiMetadata(KLumiMetadata * lumiMetadata)
	{
		this->lumiMetadata = lumiMetadata;
	}
	bool isHLTDefect()
	{
		if (!lumiMetadata)
			return true;
		for (size_t idx = 1; idx < lumiMetadata->hltNames.size(); idx++)
			if (lumiMetadata->hltPrescales[idx] == 0)
				return true;
		return false;
	}
	bool isPrescaled(std::string hltName)
	{
		return (getPrescale(hltName) > 1);
	}
	bool isAvailable(std::string hltName)
	{
		return (getHLTName(hltName) != "");
	}
	int getPrescale(std::string hltName)
	{
		if (!lumiMetadata)
			return 0;
		std::string tmpHLTName = getHLTName(hltName);
		if (tmpHLTName == "")
			return 0;
		return lumiMetadata->hltPrescales[find(lumiMetadata->hltNames.begin(), lumiMetadata->hltNames.end(), tmpHLTName) - lumiMetadata->hltNames.begin()];
	}
	std::string getHLTName(std::string hltName)
	{
		if (!lumiMetadata)
			return "";
		std::vector<std::string>::iterator endIt = lumiMetadata->hltNames.end();
		std::vector<std::string>::iterator curIt = find(lumiMetadata->hltNames.begin(), endIt, hltName);
		if (curIt != endIt)
			return *curIt;
		boost::regex pattern(hltName+"(_v[[:digit:]]+)?$", boost::regex::icase | boost::regex::extended);
		for (curIt = lumiMetadata->hltNames.begin(); curIt != endIt; ++curIt)
			if (boost::regex_search(*curIt, pattern))
				return *curIt;
		return "";
	}
};

#endif
