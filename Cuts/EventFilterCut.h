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
			unsigned long nBX;
		public:
			RunLumiEvtBXRange(unsigned long nRun_, unsigned long nLumiMin_, unsigned long nLumiMax_, unsigned long nBX_) :
				nRun(nRun_),
				nLumiMin(nLumiMin_),
				nLumiMax(nLumiMax_),
				nBX(nBX_)
				{};
			bool contains(KEventMetadata * evt)
			{
				if (evt->nRun != nRun)
					return false;
				if (evt->nBX != nBX)
					return false;
				
				if (nLumiMin==0 && nLumiMax == 0)
					return true;
					
				if (nLumiMin==0 && evt->nLumi<=nLumiMax)
					return true;

				if (nLumiMin<=evt->nLumi && nLumiMax == 0)
					return true;

				if (nLumiMin<=evt->nLumi && evt->nLumi<=nLumiMax)
					return true;
					
				return false;
			}
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
			bool getInternalDecision();
			double getDecisionValue();
	};
}
#endif

