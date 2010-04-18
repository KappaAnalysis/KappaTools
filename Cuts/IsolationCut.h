#ifndef KIsolationCut_h
#define KIsolationCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KMuon.h"

namespace KappaTools
{
	template <typename T>
	class IsolationCut : public BaseCut
	{
		private:
			T * obj;
			double min;
			double max;
			double coneSize;
			unsigned char isoType;
		public:
			const static unsigned char TRACKISO = 0;
			const static unsigned char ECALISO  = 1;
			const static unsigned char HCALISO  = 2;
			const static unsigned char RELCOMBISO  = 3;

			IsolationCut();
			IsolationCut(T * tmpObj);
			IsolationCut(unsigned char isoType_, double coneSize_);

			void setPointer(T * tmpObj);

			void setType(unsigned char isoType_);
			void setConeSize(double coneSize_);
			void setMinCut(double min_);
			void setMaxCut(double max_);

			virtual bool getInternalDecision();

			double getDecisionValue();
	};
}
#endif

