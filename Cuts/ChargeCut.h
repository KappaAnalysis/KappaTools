#ifndef KChargeCut_h
#define KChargeCut_h

#include "BaseCut.h"
#include <vector>
#include <algorithm>

namespace KappaTools
{
	template <typename T>
	class ChargeCut : public BaseCut
	{
		private:
			std::vector< T * > obj;
			std::vector< int > allowed_charges;
		public:
			ChargeCut();
			ChargeCut(T * tmpObj);
			void setPointer(T * tmpObj);
			void setPointer(T * tmpObj1, T * tmpObj2);
			void addPointer(T * tmpObj);
			void setPointer(std::vector< T * > tmpObj);
			
			void setCut(int allowed_charge_);
			void setCut(std::vector<int> allowed_charges_);
			void addCut(int allowed_charge_);
			
			bool getInternalDecision();
			double getDecisionValue();
	};

	template <typename T>
	ChargeCut<T>::ChargeCut() : BaseCut("charge cut")	{}
	
	template <typename T>
	ChargeCut<T>::ChargeCut(T * tmpObj) : BaseCut("charge cut")
	{
		obj.push_back(tmpObj);
	}
		
	template <typename T>
	void ChargeCut<T>::setPointer(T * tmpObj)
	{
		obj.clear();
		obj.push_back(tmpObj);														
	}
	
	template <typename T>
	void ChargeCut<T>::setPointer(T * tmpObj1, T * tmpObj2)
	{	
		obj.clear();
		obj.push_back(tmpObj1);
		obj.push_back(tmpObj2);
	}
	
	template <typename T>
	void ChargeCut<T>::addPointer(T * tmpObj)
	{
		obj.push_back(tmpObj);
	}
	
	template <typename T>
	void ChargeCut<T>::setPointer(std::vector< T * > tmpObj)
	{
		obj.clear();
		obj=tmpObj;
	}

	template <typename T>
	void ChargeCut<T>::setCut(int allowed_charge_)
	{ 
		allowed_charges.clear();
		allowed_charges.push_back(allowed_charge_);
	}
	
	template <typename T>
	void ChargeCut<T>::setCut(std::vector<int> allowed_charges_)
	{
		allowed_charges = allowed_charges_;
	}
	
	template <typename T>
	void ChargeCut<T>::addCut(int allowed_charge_)
	{
		allowed_charges.push_back(allowed_charge_);
	}

	template <typename T>
	bool ChargeCut<T>::getInternalDecision()
	{
		if (obj.size()==0)
			return false;
	
		int sum=0;
		for (typename std::vector< T * >::iterator it = obj.begin(); it!=obj.end(); it++)
			if (*it)
				sum+=(*it)->charge;
	
		return (find(allowed_charges.begin(), allowed_charges.end(),sum) != allowed_charges.end());
	};

	template <typename T>
	double ChargeCut<T>::getDecisionValue()
	{
		int sum=0;
		for (typename std::vector< T * >::iterator it = obj.begin(); it!=obj.end(); it++)
			sum+=(*it)->charge; 
		return sum; 
	};
}
#endif
