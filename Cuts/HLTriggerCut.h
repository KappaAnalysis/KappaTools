#ifndef KHLTriggerCut_h
#define KHLTriggerCut_h

#include "BaseCut.h"
#include "Kappa/DataFormats/interface/KMetadata.h"
#include <boost/algorithm/string/regex.hpp>
#include <vector>

namespace KappaTools
{
	class HLTriggerCut : public BaseCut
	{
	private:
		KEventMetadata * obj;
		std::map<std::string, int> hltMap;
		std::vector<std::string> selected;
		int min, max;
		int firedTriggers;
	public:
		HLTriggerCut();
		HLTriggerCut(KEventMetadata * tempObj);
		HLTriggerCut(KEventMetadata * tempObj, std::vector<std::string> selected_);
		HLTriggerCut(std::vector<std::string> selected_);
		HLTriggerCut(KEventMetadata * tempObj, std::vector<std::string> selected_, int min_);
		HLTriggerCut(KEventMetadata * tempObj, std::vector<std::string> selected_, int min_, int max_);

		void setTriggerMap(const KLumiMetadata * tmpLumiMetadata);
		void setTrigger(std::vector<std::string> selected_);
		void setTrigger(std::string selected_);
		void setTriggerFuzzy(std::string selected_);
		void setPointer(KEventMetadata * tmpObj);
		void setCut(int min_);
		void setCut(int min_, int max_);
		void setMinCut(int min_);
		void setMaxCut(int max_);

		bool isTriggerAvailable();
		bool getInternalDecision();
		double getDecisionValue();
	};
}
#endif
