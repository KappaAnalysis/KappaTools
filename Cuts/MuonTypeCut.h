#ifndef KMuonTypeCut_h
#define KMuonTypeCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KMuon.h"

namespace KappaTools
{
	class MuonTypeCut : public BaseCut
	{
		private:
			KDataMuon * obj;
			unsigned char type;
		public:
			static const char TRACKER    = 1;
			static const char CALO       = 2;
			static const char STANDALONE = 4;
			static const char GLOBAL     = 8;
			
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

