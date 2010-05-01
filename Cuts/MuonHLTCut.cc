#include "MuonHLTCut.h"

namespace KappaTools
{
	MuonHLTCut::MuonHLTCut() : BaseCut("muon hlt cut"), obj(0), type("") {}
	MuonHLTCut::MuonHLTCut(KDataMuon * tempObj) : BaseCut("muon hlt cut"), obj(tempObj), type("") {}
	MuonHLTCut::MuonHLTCut(std::string type_) : BaseCut("muon hlt cut"), obj(0), type(type_) {}

	void MuonHLTCut::setType(std::string type_)
	{
		type = type_;
	}

	void MuonHLTCut::setPointer(KDataMuon * tmpObj)
	{
		obj=tmpObj;
	}

	bool MuonHLTCut::getInternalDecision()
	{
		if (!obj)
			return false;

		//if ((getDecisionValue() > 0.))
		//	for (std::map<std::string, int>::iterator it = hltMap.begin(); it!=hltMap.end(); it++)
		//		std::cout << "\t" << it->first << " " << it->second <<"\n";
		return (getDecisionValue() > 0.);
	}

	double MuonHLTCut::getDecisionValue()
	{
		if (!obj)
			return -1.;

		if (hltMap.find(type) == hltMap.end())
		{
			std::cout << "trigger " << type << " not available\n";
			for (std::map<std::string, int>::iterator it = hltMap.begin(); it!=hltMap.end(); it++)
				std::cout << "\t" << it->first << " available\n";
			return -1.;
		}

		//if (obj->hltMatch > 0)
		//	std::cout << "!!!!!!!!!!!!\n";
		//std::cout << type << "\t" << hltMap[type] << "\t" << obj->hltMatch << "\n";
		if ( ( obj->hltMatch & ( (unsigned long long)1 << hltMap[type] ) ) != 0 )
			return 1.;
		else
			return 0.;
	}

	void MuonHLTCut::setTriggerMap(KLumiMetadata * tmpLumiMetadata)
	{
		std::map<std::string, int> tmpMuonHltNamesMap;

		int idx=0;
		for (std::vector<std::string>::iterator it = tmpLumiMetadata->hltNamesMuons.begin(); it != tmpLumiMetadata->hltNamesMuons.end(); it++)
		{
			std::string tmpName = *it;

			if (tmpMuonHltNamesMap[tmpName])
				continue;

			//std::cout << "muon-Objekte: " << tmpName << " " << idx << "\n";
			tmpMuonHltNamesMap[tmpName] = idx++;
		}
		hltMap=tmpMuonHltNamesMap;

		//std::cout << "\n";
	}
}
