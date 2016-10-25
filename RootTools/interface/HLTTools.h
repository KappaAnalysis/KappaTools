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
	KLumiInfo * lumiInfo;
	unsigned int akt_nLumi; // trigger will not change in the same lumi section
	unsigned int akt_nRun; // also check for the rare cases if file will change, but lumi is kept
	bool refill_hlt; // will be used for the refill of the chaces. Which takes some time O(100 ms)
	
	
public:
	HLTTools(KLumiInfo * lumiInfo = nullptr)
	{
	  akt_nLumi = 0; // just a default value, will be overwritten by first lumi
	  akt_nRun = 0;// just a default value, will be overwritten by first lumi
	  refill_hlt = true; // Allways fill the hlt infos in the first run
	  if (lumiInfo){
	    setLumiInfo(lumiInfo);
	  }
	}
	void setLumiInfo(KLumiInfo * lumiInfo)
	{
		this->lumiInfo = lumiInfo;		
		if (lumiInfo->nLumi != akt_nLumi || lumiInfo->nRun != akt_nRun){ // check if lumi or run number has changed
		  akt_nLumi = lumiInfo->nLumi; // save new lumi
		  akt_nRun  = lumiInfo->nRun; // save new akt run
		  refill_hlt = true; // tirgger new refill
		}
		
		if (refill_hlt){
		  nameCache.clear();
		  posCache.clear();
		  for (size_t idx = 0; idx < lumiInfo->hltNames.size(); ++idx){
		    posCache[lumiInfo->hltNames[idx]] = idx;
		    nameCache[lumiInfo->hltNames[idx]] = lumiInfo->hltNames[idx];
		  }
		  nameCacheEndIt = nameCache.end();
		  refill_hlt = false;	
		}
	}
	bool isHLTDefect() const
	{
		if (!lumiInfo)
			return true;
		for (size_t idx = 1; idx < lumiInfo->hltNames.size(); idx++)
			if (!lumiInfo->hltPrescales[idx])
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
	unsigned int getPrescale(const std::string &hltName) const
	{
		if (!lumiInfo)
			return 0;
		std::string tmpHLTName = getHLTName(hltName);
		if (tmpHLTName == "")
			return 0;
		return lumiInfo->hltPrescales[posCache[tmpHLTName]];
	}
	std::string getHLTName(const std::string &hltName) const
	{
		itCache = nameCache.find(hltName);
		if (itCache != nameCacheEndIt)
			return itCache->second;

		if (!lumiInfo)
			return "";

		std::vector<std::string>::const_iterator endIt = lumiInfo->hltNames.end();
		boost::regex pattern(hltName+"(_v[[:digit:]]+)?$", boost::regex::icase | boost::regex::extended);
		for (std::vector<std::string>::const_iterator curIt = lumiInfo->hltNames.begin(); curIt != endIt; ++curIt)
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
