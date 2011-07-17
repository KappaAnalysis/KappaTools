#ifndef KInvariantMassCut_h
#define KInvariantMassCut_h

#include "BaseCut.h"
#include "Kappa/DataFormats/interface/KLorentzVector.h"
#include "Kappa/DataFormats/interface/KBasic.h"
#include "Kappa/DataFormats/interface/KMuon.h"
#include "Kappa/DataFormats/interface/KJetMET.h"

namespace KappaTools
{
	template <typename T>
	class InvariantMassCut : public BaseCut
	{
	private:
		std::vector< T * > obj;
		double mass_min;
		double mass_max;
	public:
		InvariantMassCut();
		InvariantMassCut(T * tmpObj);

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
