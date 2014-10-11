/* Copyright (c) 2011 - All Rights Reserved
 *   Manuel Zeise <zeise@cern.ch>
 */

#ifndef KAPPA_HLTTOOLS_H
#define KAPPA_HLTTOOLS_H

#include <Kappa/DataFormats/interface/Kappa.h>
#include <boost/regex.hpp>

class HLTTools
{
private:
	mutable std::map<std::string, std::string> nameCache;
	mutable std::map<std::string, std::string>::iterator itCache;
	mutable std::map<std::string, std::string>::iterator nameCacheEndIt;
	mutable std::map<std::string, size_t> posCache;
	KLumiMetadata * lumiMetadata;
public:
	HLTTools(KLumiMetadata * lumiMetadata = 0)
	{
		if (lumiMetadata)
			setLumiMetadata(lumiMetadata);
	}
	void setLumiMetadata(KLumiMetadata * lumiMetadata)
	{
		this->lumiMetadata = lumiMetadata;
		nameCache.clear();
		posCache.clear();
		for (size_t idx=0; idx < lumiMetadata->hltNames.size(); ++idx)
		{
			posCache[lumiMetadata->hltNames[idx]] = idx;
			nameCache[lumiMetadata->hltNames[idx]] = lumiMetadata->hltNames[idx];
		}
		nameCacheEndIt = nameCache.end();
	}
	bool isHLTDefect() const
	{
		if (!lumiMetadata)
			return true;
		for (size_t idx = 1; idx < lumiMetadata->hltNames.size(); idx++)
			if (!lumiMetadata->hltPrescales[idx])
				return true;
		return false;
	}
	bool isPrescaled(const std::string &hltName) const
	{
		return (getPrescale(hltName) > 1);
	}
	bool isAvailable(const std::string &hltName) const
	{
		return (getHLTName(hltName) != "");
	}
	int getPrescale(const std::string &hltName) const
	{
		if (!lumiMetadata)
			return 0;
		std::string tmpHLTName = getHLTName(hltName);
		if (tmpHLTName == "")
			return 0;
		return lumiMetadata->hltPrescales[posCache[tmpHLTName]];
	}
	std::string getHLTName(const std::string &hltName) const
	{
		itCache = nameCache.find(hltName);
		if (itCache != nameCacheEndIt)
			return itCache->second;

		if (!lumiMetadata)
			return "";

		std::vector<std::string>::const_iterator endIt = lumiMetadata->hltNames.end();
		boost::regex pattern(hltName+"(_v[[:digit:]]+)?$", boost::regex::icase | boost::regex::extended);
		for (std::vector<std::string>::const_iterator curIt = lumiMetadata->hltNames.begin(); curIt != endIt; ++curIt)
			if (boost::regex_search(*curIt, pattern))
			{
				nameCache[hltName] = *curIt;
				nameCacheEndIt = nameCache.end();
				return *curIt;
			}
		return "";
	}
	size_t getHLTPosition(const std::string &hltName) const
	{
		std::string tmpHLTName = getHLTName(hltName);
		if (tmpHLTName == "")
			return 0;
		return posCache[tmpHLTName];
	}

};

#endif
