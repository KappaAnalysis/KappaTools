#ifndef KDeltaRCut_h
#define KDeltaRCut_h

#include "BaseCut.h"
#include "Math/GenVector/VectorUtil.h"
#include "DataFormats/interface/KLorentzVector.h"

namespace KappaTools
{
	template <typename T1, typename T2>
	class DeltaRCut : public BaseCut
	{
		private:
			T1 * obj1;
			T2 * obj2;
			double dR_min;
			double dR_max;
		public:
			DeltaRCut();
			void setPointer(T1 * tmpObj1, T2 * tmpObj2);
			void setMinCut(double tmpdR_min);
			void setMaxCut(double tmpdR_max);
			bool getInternalDecision();
			
			double getDecisionValue();
	};
}
#endif
