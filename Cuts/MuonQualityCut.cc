#include "MuonQualityCut.h"

namespace KappaTools
{
	MuonQualityCut::MuonQualityCut() : BaseCut("muon type cut"), obj(0), type(MuonQualityCut::All) {}
	MuonQualityCut::MuonQualityCut(KDataMuon * tempObj) : BaseCut("muon type cut"), obj(tempObj), type(MuonQualityCut::All) {}
	MuonQualityCut::MuonQualityCut(unsigned int type_) : BaseCut("muon type cut"), obj(0), type(type_) {}

	void MuonQualityCut::setType(unsigned int type_)
	{
		type = type_;
	}

	void MuonQualityCut::setPointer(KDataMuon * tmpObj)
	{
		obj=tmpObj;
	}

	bool MuonQualityCut::getInternalDecision()
	{
		if (!obj)
			return false;
		return (obj->type & type);
	}

	double MuonQualityCut::getDecisionValue()
	{
		if (!obj)
			return 0;
		return (obj->type);
	}
}
