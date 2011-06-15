#ifndef KEtaCut_h
#define KEtaCut_h

#include "BaseCut.h"
#include "Kappa/DataFormats/interface/KLorentzVector.h"
#include "Kappa/DataFormats/interface/KBasic.h"
#include "Kappa/DataFormats/interface/KMuon.h"
#include "Kappa/DataFormats/interface/KTau.h"
#include "Kappa/DataFormats/interface/KJetMET.h"

namespace KappaTools
{
	template <typename T>
	class EtaCut : public BaseCut
	{
	private:
		const T * obj;
		double eta_min;
		double eta_max;
	public:
		EtaCut();
		EtaCut(const T * tmpObj);

		void setPointer(const T * tmpObj);

		void setCut(double eta_max_);
		void setCut(double eta_min_, double eta_max_);
		void setMinCut(double eta_min_);
		void setMaxCut(double eta_max_);

		virtual bool getInternalDecision();
		double getDecisionValue();
	};
}
#endif
