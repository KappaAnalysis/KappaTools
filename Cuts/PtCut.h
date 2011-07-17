#ifndef KPtCut_h
#define KPtCut_h

#include "BaseCut.h"
#include "Kappa/DataFormats/interface/KLorentzVector.h"
#include "Kappa/DataFormats/interface/KBasic.h"
#include "Kappa/DataFormats/interface/KMuon.h"
#include "Kappa/DataFormats/interface/KJetMET.h"
#include "Kappa/DataFormats/interface/KTau.h"

namespace KappaTools
{
	template <typename T>
	class PtCut : public BaseCut
	{
	private:
		const T * obj;
		double pt_min;
		double pt_max;
	public:
		PtCut();
		PtCut(const T * tmpObj);

		void setPointer(const T * tmpObj);

		void setMinCut(double pt_min_);
		void setMaxCut(double pt_max_);

		virtual bool getInternalDecision();
		double getDecisionValue();
	};
}
#endif
