#ifndef LUMICOUNTER
#define LUMICOUNTER

#include <string>
#include <map>
#include <set>

#include "Kappa/DataFormats/interface/Kappa.h"

class LumiCounter
{
private:
	double sumLumi;
	std::set< std::pair<run_id, lumi_id> > alreadyAdded;
	std::map< std::string, double > catLumi;

public:
	LumiCounter() : sumLumi(0) {}

	bool count(const KDataLumiMetadata * lumi, const std::string category = "")
	{
		if (!lumi)
			return false;
		if (alreadyAdded.find(std::make_pair(lumi->nRun, lumi->nLumi)) != alreadyAdded.end())
			return false;
		
		alreadyAdded.insert(std::make_pair(lumi->nRun, lumi->nLumi));

		sumLumi += lumi->getLumi();
		catLumi[category] = lumi->getLumi();
		return true;
	}

	double getLumi(const std::string category = "") const
	{
		if (category == "")
			return sumLumi;
			
		std::map< std::string, double >::const_iterator itSearch = catLumi.find(category);
		if (itSearch != catLumi.end())
			return itSearch->second;
		else
			return 0;
	}
};
#endif
