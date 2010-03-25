#ifndef KVertexNdofCut_h
#define KVertexNdofCut_h

#include "BaseCut.h"
#include <vector>
#include "DataFormats/interface/KBasic.h"

namespace KappaTools
{
	class VertexNdofCut : public BaseCut
	{
		private:
			KDataVertex * obj;
			double min;
			double max;
		public:
			VertexNdofCut() : BaseCut("pv ndof cut"), obj(0), min(0.), max(1.) {};
			VertexNdofCut(KDataVertex * tmpObj) : BaseCut("pv ndof cut"), obj(tmpObj), min(0.), max(1.) {};
		
			void setPointer(KDataVertex * tmpObj);
			
			void setMinCut(double min_);
			void setMaxCut(double max_);
		
			virtual bool getInternalDecision();
			double getDecisionValue();
	};
	
	void VertexNdofCut::setPointer(KDataVertex * tmpObj)
	{
		obj=tmpObj;
	}

	void VertexNdofCut::setMinCut(double min_)
	{
		min=min_;
	}

	void VertexNdofCut::setMaxCut(double max_)
	{
		max=max_;
	}

	bool VertexNdofCut::getInternalDecision()
	{
		if (!obj)
			return false;
	
		double val = getDecisionValue();
	
		return (val>min && val<max);
	};

	double VertexNdofCut::getDecisionValue()
	{
		if (!obj)
			return -1.;

		return obj->nDOF;
	};
}
#endif
