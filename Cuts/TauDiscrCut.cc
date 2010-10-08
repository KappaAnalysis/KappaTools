#include "TauDiscrCut.h"

namespace KappaTools
{
	TauDiscrCut::TauDiscrCut(): BaseCut("tau discriminant cut"), obj(0), index(-1) {}
	TauDiscrCut::TauDiscrCut(const std::string& discr): BaseCut("tau discriminant cut"), obj(0), discr(discr), index(-1) {}

	void TauDiscrCut::setDiscr(const std::string& discr)
	{
		this->discr = discr;
		this->index = -1; // invalidate... need to call setDiscrMapCalo or setDiscrMapPF to revalidate
	}

	bool TauDiscrCut::setDiscrMapCalo(const KLumiMetadata * tmpLumiMetadata)
	{
		for(size_t i = 0; i < tmpLumiMetadata->discrTau.size(); ++i)
			if(tmpLumiMetadata->discrTau[i] == discr)
				{ index = i; return true; }

		index = -1;
		return false;
	}

	bool TauDiscrCut::setDiscrMapPF(const KLumiMetadata * tmpLumiMetadata)
	{
		for(size_t i = 0; i < tmpLumiMetadata->discrTauPF.size(); ++i)
			if(tmpLumiMetadata->discrTauPF[i] == discr)
				{ index = i; return true; }

		index = -1;
		return false;
	}

	void TauDiscrCut::setPointer(const KDataTau * tmpObj)
	{
		obj = tmpObj;
	}

	bool TauDiscrCut::getInternalDecision()
	{
		if (!obj)
			return false;

		return (getDecisionValue() > 0.);
	}

	double TauDiscrCut::getDecisionValue()
	{
		if (!obj)
			return -1.;
		if(index == -1)
		{
			std::cout << "TauDiscrCut: No discriminant map loaded. Call setDiscrMapPF or setDiscrMapCalo" << std::endl;
			return -1.0;
		}

		if(obj->discr & (1ull << index)) return 1.0;
		return 0.0;
	}
}
