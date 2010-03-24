#ifndef KPtCut_h
#define KPtCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KLorentzVector.h"

namespace KappaTools
{
	template <typename T>
	class PtCut : public BaseCut
	{
		private:
			T * obj;
			double pt_min;
			double pt_max;
		public:
			PtCut();
			PtCut(T * tmpObj);
			
			void setPointer(T * tmpObj);
				
			void setMinCut(double pt_min_);
			void setMaxCut(double pt_max_);
			
			virtual bool getInternalDecision();
			double getDecisionValue();
	};

	template <typename T>
	PtCut<T>::PtCut()	: BaseCut("pT cut"), obj(0), pt_min(0.), pt_max(1e6) {}
	
	template <typename T>
	PtCut<T>::PtCut(T * tmpObj) : BaseCut("pT cut"), obj(tmpObj), pt_min(0.), pt_max(1e6) {}

	template <typename T>
	void PtCut<T>::setPointer(T * tmpObj)
	{
		obj = tmpObj;
	}
	
	template <typename T>
	void PtCut<T>::setMinCut(double pt_min_)
	{
		pt_min = pt_min_;
	}
	
	template <typename T>
	void PtCut<T>::setMaxCut(double pt_max_)
	{
		pt_max = pt_max_;
	}

	template <typename T>
	bool PtCut<T>::getInternalDecision()
	{
		if (!obj)
			return false;
		
		double val = getDecisionValue();
		return (val>pt_min && val<pt_max);
	};

	template <typename T>
	double PtCut<T>::getDecisionValue()
	{
		if (!obj)
			return -1.;
		else
			return obj->p4.pt();
	};
}
#endif
