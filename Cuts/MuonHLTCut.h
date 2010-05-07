#ifndef KMuonHLTCut_h
#define KMuonHLTCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KMuon.h"
#include "DataFormats/interface/KMetadata.h"

namespace KappaTools
{
	class MuonHLTCut : public BaseCut
	{
		private:
			KDataMuon * obj;
			std::string type;
			std::map<std::string, int> hltMap;
		public:
			MuonHLTCut();
			MuonHLTCut(KDataMuon * tempObj);
			MuonHLTCut(std::string type_);

			bool isTriggerAvailable();
			void setTriggerMap(KLumiMetadata * tmpLumiMetadata);

			void setType(std::string type);
			void setPointer(KDataMuon * tmpObj);

			bool getInternalDecision();
			double getDecisionValue();
	};
}

#endif
