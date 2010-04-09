#ifndef KUserBitFlagsCut_h
#define KUserBitFlagsCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KMetadata.h"
#include <vector>

namespace KappaTools
{
	class UserBitFlagsCut : public BaseCut
	{
		private:
			KEventMetadata * obj;
			std::vector<unsigned long> selected;
			int min, max;
			int firedTriggers;
		public:
			UserBitFlagsCut();
			UserBitFlagsCut(KEventMetadata * tempObj);
			UserBitFlagsCut(KEventMetadata * tempObj, std::vector<unsigned long> selected_);
			UserBitFlagsCut(std::vector<unsigned long> selected_);
			UserBitFlagsCut(KEventMetadata * tempObj, std::vector<unsigned long> selected_, int min_);
			UserBitFlagsCut(KEventMetadata * tempObj, std::vector<unsigned long> selected_, int min_, int max_);

			void setTrigger(std::vector<unsigned long> selected_);
			void setPointer(KEventMetadata * tmpObj);
			void setCut(int min_);
			void setCut(int min_, int max_);
			void setMinCut(int min_);
			void setMaxCut(int max_);

			bool getInternalDecision();
			double getDecisionValue();
	};
}
#endif
