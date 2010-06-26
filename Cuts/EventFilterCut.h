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
			run_id nRun;
			lumi_id nLumiMin;
			lumi_id nLumiMax;
			bx_id nBX;
		public:
			RunLumiEvtBXRange(run_id nRun_, lumi_id nLumiMin_ = 0, lumi_id nLumiMax_ = 0, bx_id nBX_ = 0);
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

			void addRange(std::vector<RunLumiEvtBXRange> range_);
			void addRange(RunLumiEvtBXRange range_);
			void clearList();
			std::vector<unsigned long> getRuns();
			bool getInternalDecision();
			double getDecisionValue();
	};
}

#endif
