#ifndef KTauDiscrCut_h
#define KTauDiscrCut_h

#include "BaseCut.h"
#include "Kappa/DataFormats/interface/KTau.h"
#include "Kappa/DataFormats/interface/KMetadata.h"

namespace KappaTools
{
	class TauDiscrCut : public BaseCut
	{
	private:
		const KDataTau * obj;
		std::string discr;
		int index;
	public:
		TauDiscrCut();
		TauDiscrCut(const std::string& discr);

		void setDiscr(const std::string& discr);
		bool setDiscrMapCalo(const KLumiMetadata * tmpLumiMetadata);
		bool setDiscrMapPF(const KLumiMetadata * tmpLumiMetadata);
		void setPointer(const KDataTau * tmpObj);

		bool getInternalDecision();
		double getDecisionValue();
	};
}

#endif
