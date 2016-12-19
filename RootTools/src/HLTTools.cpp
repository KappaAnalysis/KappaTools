
#include "../interface/HLTTools.h"

#include <boost/regex.hpp>


HLTTools::HLTTools(KLumiInfo * lumiInfo)
{
	akt_nLumi = 0; // just a default value, will be overwritten by first lumi
	akt_nRun = 0;// just a default value, will be overwritten by first lumi
	refill_hlt = true; // Allways fill the hlt infos in the first run
	if (lumiInfo){
		setLumiInfo(lumiInfo);
	}
}
void HLTTools::setLumiInfo(KLumiInfo * lumiInfo)
{
	this->lumiInfo = lumiInfo;
	if (lumiInfo->nLumi != akt_nLumi || lumiInfo->nRun != akt_nRun){ // check if lumi or run number has changed
		akt_nLumi = lumiInfo->nLumi; // save new lumi
		akt_nRun = lumiInfo->nRun; // save new akt run
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
bool HLTTools::isHLTDefect() const
{
	if (!lumiInfo)
		return true;
	for (size_t idx = 1; idx < lumiInfo->hltNames.size(); idx++)
		if (!lumiInfo->hltPrescales[idx])
			return true;
	return false;
}
bool HLTTools::isPrescaled(const std::string &hltName) const
{
	return (getPrescale(hltName) > 1);
}
bool HLTTools::isAvailable(const std::string &hltName) const
{
	return (getHLTName(hltName) != "");
}
unsigned int HLTTools::getPrescale(const std::string &hltName) const
{
	if (!lumiInfo)
		return 0;
	std::string tmpHLTName = getHLTName(hltName);
	if (tmpHLTName == "")
		return 0;
	return lumiInfo->hltPrescales[posCache[tmpHLTName]];
}
std::string HLTTools::getHLTName(const std::string &hltName) const
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
size_t HLTTools::getHLTPosition(const std::string &hltName) const
{
	std::string tmpHLTName = getHLTName(hltName);
	if (tmpHLTName == "")
		return 0;
	return posCache[tmpHLTName];
}

