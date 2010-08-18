#ifndef KEtaCut_h
#define KEtaCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KLorentzVector.h"
#include "DataFormats/interface/KBasic.h"
#include "DataFormats/interface/KMuon.h"
#include "DataFormats/interface/KTau.h"
#include "DataFormats/interface/KJetMET.h"

namespace KappaTools
{
	template <typename T>
	class EtaCut : public BaseCut
	{
		private:
			T * obj;
			double eta_min;
			double eta_max;
		public:
			EtaCut();
			EtaCut(T * tmpObj);

			void setPointer(T * tmpObj);

			void setCut(double eta_max_);
			void setCut(double eta_min_, double eta_max_);
			void setMinCut(double eta_min_);
			void setMaxCut(double eta_max_);

			virtual bool getInternalDecision();
			double getDecisionValue();
	};
}
#endif
