#include "MuonTypeCut.h"

namespace KappaTools
{
	MuonTypeCut::MuonTypeCut() : BaseCut("muon type cut"), obj(0), type(GLOBAL) {}
	MuonTypeCut::MuonTypeCut(KDataMuon * tempObj) : BaseCut("muon type cut"), obj(tempObj), type(GLOBAL) {}
	MuonTypeCut::MuonTypeCut(unsigned char type_) : BaseCut("muon type cut"), obj(0), type(type_) {}

	void MuonTypeCut::setType(unsigned char type_)
	{
		type = type_;
	}

	void MuonTypeCut::setPointer(KDataMuon * tmpObj)
	{
		obj = tmpObj;
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
