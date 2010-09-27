#ifndef KPtCut_h
#define KPtCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KLorentzVector.h"
#include "DataFormats/interface/KBasic.h"
#include "DataFormats/interface/KMuon.h"
#include "DataFormats/interface/KJetMET.h"
#include "DataFormats/interface/KTau.h"

namespace KappaTools
{
	template <typename T>
	class PtCut : public BaseCut
	{
	private:
		T * obj;
		double pt_min;
		double pt_max;
	public:
		PtCut();
		PtCut(T * tmpObj);

		void setPointer(T * tmpObj);

		void setMinCut(double pt_min_);
		void setMaxCut(double pt_max_);

		virtual bool getInternalDecision();
		double getDecisionValue();
	};
}
#endif
