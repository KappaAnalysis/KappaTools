#ifndef KMuonHLTCut_h
#define KMuonHLTCut_h

#include "BaseCut.h"
#include "Kappa/DataFormats/interface/KMuon.h"
#include "Kappa/DataFormats/interface/KMetadata.h"

namespace KappaTools
{
	class MuonHLTCut : public BaseCut
	{
	private:
		const KDataMuon * obj;
		std::string type;
		std::map<std::string, int> hltMap;
	public:
		MuonHLTCut();
		MuonHLTCut(const KDataMuon * tempObj);
		MuonHLTCut(std::string type_);

		bool isTriggerAvailable();
		void setTriggerMap(const KLumiMetadata * tmpLumiMetadata);

		void setType(std::string type);
		void setPointer(const KDataMuon * tmpObj);

		bool getInternalDecision();
		double getDecisionValue();
	};
}

#endif
