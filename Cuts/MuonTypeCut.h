#ifndef KMuonTypeCut_h
#define KMuonTypeCut_h

#include "BaseCut.h"
#include "Kappa/DataFormats/interface/KMuon.h"

namespace KappaTools
{
	class MuonTypeCut : public BaseCut
	{
	private:
		KDataMuon * obj;
		unsigned char type;
	public:
		static const char GLOBAL     = 1 << 1;
		static const char TRACKER    = 1 << 2;
		static const char STANDALONE = 1 << 3;
		static const char CALO       = 1 << 4;

		MuonTypeCut();
		MuonTypeCut(KDataMuon * tempObj);
		MuonTypeCut(unsigned char type_);

		void setType(unsigned char type);
		void setPointer(KDataMuon * tmpObj);

		bool getInternalDecision();
		double getDecisionValue();
	};
}

#endif

