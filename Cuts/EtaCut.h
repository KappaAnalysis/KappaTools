#ifndef KEtaCut_h
#define KEtaCut_h

#include "BaseCut.h"
#include "DataFormats/interface/KLorentzVector.h"

namespace KappaTools
{
	template <typename T>
	class EtaCut : public BaseCut
	{
		private:
			T * obj;
			double eta_min;
			double eta_max;
		public:
			EtaCut();
			EtaCut(T * tmpObj);
			
			void setPointer(T * tmpObj);
				
			void setMinCut(double eta_min_);
			void setMaxCut(double eta_max_);
			
			virtual bool getInternalDecision();
			double getDecisionValue();
	};

	template <typename T>
	EtaCut<T>::EtaCut()	: BaseCut("eta cut"), obj(0), eta_min(0.), eta_max(1e6) {}
	
	template <typename T>
	EtaCut<T>::EtaCut(T * tmpObj) : BaseCut("eta cut"), obj(tmpObj), eta_min(0.), eta_max(1e6) {}

	template <typename T>
	void EtaCut<T>::setPointer(T * tmpObj)
	{
		obj = tmpObj;
	}
	
	template <typename T>
	void EtaCut<T>::setMinCut(double eta_min_)
	{
		eta_min = eta_min_;
	}
	
	template <typename T>
	void EtaCut<T>::setMaxCut(double eta_max_)
	{
		eta_max = eta_max_;
	}

	template <typename T>
	bool EtaCut<T>::getInternalDecision()
	{
		if (!obj)
			return false;
		
		double val = getDecisionValue();
		return (val>eta_min && val<eta_max);
	};

	template <typename T>
	double EtaCut<T>::getDecisionValue()
	{
		if (!obj)
			return -1.;
		else
			return obj->p4.eta();
	};
}
#endif
