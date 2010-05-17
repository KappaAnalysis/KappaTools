#ifndef KEventFilterCut_h
#define KEventFilterCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KMetadata.h"
#include <vector>

namespace KappaTools
{
	class RunLumiEvtBXRange
	{
		private:
			unsigned long nRun;
			unsigned long nLumiMin;
			unsigned long nLumiMax;
			int nBX;
		public:
			RunLumiEvtBXRange(unsigned long nRun_, unsigned long nLumiMin_ = 0, unsigned long nLumiMax_ = 0, int nBX_ = 0);
			bool contains(KEventMetadata * evt);
			unsigned long getRun();
	};
	
	class EventFilterCut : public BaseCut
	{
		private:
			KEventMetadata * obj;
			std::vector<RunLumiEvtBXRange> whitelist;
		public:
			EventFilterCut();
			EventFilterCut(KEventMetadata * tempObj);

			void setPointer(KEventMetadata * tmpObj);

			void addRange(RunLumiEvtBXRange range_);
			void clearList();
			std::vector<unsigned long> getRuns();
			bool getInternalDecision();
			double getDecisionValue();
	};
}
#endif

