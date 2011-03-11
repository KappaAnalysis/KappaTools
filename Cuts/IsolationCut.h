#ifndef KIsolationCut_h
#define KIsolationCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KMuon.h"
#include "DataFormats/interface/KJetMET.h"

namespace KappaTools
{
	template <typename T>
	class IsolationCut : public BaseCut
	{
	private:
		T * obj;
#ifdef KAPPA_FEATURE_JETAREA
		KJetArea * jetAreaInfo;
#endif
		double min;
		double max;
		double coneSize;
		unsigned char isoType;
		bool pileUpSubstraction;
	public:
		const static unsigned char TRACKISO = 0;
		const static unsigned char ECALISO  = 1;
		const static unsigned char HCALISO  = 2;
		const static unsigned char RELCOMBISO  = 3;
		const static unsigned char SUMPTISO = 4;

		IsolationCut();
		IsolationCut(T * tmpObj);
		IsolationCut(unsigned char isoType_, double coneSize_);

#ifdef KAPPA_FEATURE_JETAREA
		void setPointer(T * tmpObj, KJetArea * tmpJetAreaInfo = 0);
#else
		void setPointer(T * tmpObj);
#endif

		void setType(unsigned char isoType_);
		void setConeSize(double coneSize_);
		void setMinCut(double min_);
		void setMaxCut(double max_);
#ifdef KAPPA_FEATURE_JETAREA
		void setPUSubstraction(bool pileUpSubstraction_);
#endif
		virtual bool getInternalDecision();

		double getDecisionValue();
	};
}
#endif

