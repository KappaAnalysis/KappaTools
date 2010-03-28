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

	MuonTypeCut::MuonTypeCut() : BaseCut("muon type cut"), obj(0), type(GLOBAL) {}
	MuonTypeCut::MuonTypeCut(KDataMuon * tempObj) : BaseCut("muon type cut"), obj(tempObj), type(GLOBAL) {}
	MuonTypeCut::MuonTypeCut(unsigned char type_) : BaseCut("muon type cut"), obj(0), type(type_) {}

	void MuonTypeCut::setType(unsigned char type_)
	{
		type = type_;
	}
	
	void MuonTypeCut::setPointer(KDataMuon * tmpObj)
	{
		obj=tmpObj;
	}

	bool MuonTypeCut::getInternalDecision()
	{
		if (!obj)
			return false;
		return (obj->type & type);
	}

	double MuonTypeCut::getDecisionValue()
	{
		if (!obj)
			return 0;
		return (obj->type);
	}
}

#endif

