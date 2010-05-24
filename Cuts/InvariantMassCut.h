#ifndef KInvariantMassCut_h
#define KInvariantMassCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KLorentzVector.h"
#include "DataFormats/interface/KBasic.h"
#include "DataFormats/interface/KMuon.h"
#include "DataFormats/interface/KJetMET.h"

namespace KappaTools
{
	template <typename T>
	class InvariantMassCut : public BaseCut
	{
		private:
			//FIXME: cut inversion should be done via BaseCut class!
			double cut_inversion;
			std::vector< T * > obj;
			double mass_min;
			double mass_max;
		public:
			InvariantMassCut();
			InvariantMassCut(T * tmpObj);
			
			void inverse(bool invert);
			void setPointer(T * tmpObj);
			void setPointer(T * tmpObj1, T * tmpObj2);
			void addPointer(T * tmpObj);
			void setPointer(std::vector< T * > tmpObj);
						
			void setCut(double mass_min_, double mass_max_);
			void setMinCut(double mass_min_);
			void setMaxCut(double mass_max_);
			
			bool getInternalDecision();
			double getDecisionValue();
	};
}
#endif

