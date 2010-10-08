#include "InvariantMassCut.h"

namespace KappaTools
{
	template <typename T>
	InvariantMassCut<T>::InvariantMassCut() : BaseCut("inv. mass cut")
	{
		mass_min = 0.;
		mass_max = 1e5;
	}

	template <typename T>
	InvariantMassCut<T>::InvariantMassCut(T * tmpObj) : BaseCut("inv. mass cut")
	{
		obj.push_back(tmpObj);
		mass_min = 0.;
		mass_max = 1e5;
	};

	template <typename T>
	void InvariantMassCut<T>::setPointer(T * tmpObj) 								{	obj.clear(); obj.push_back(tmpObj);														};

	template <typename T>
	void InvariantMassCut<T>::setPointer(T * tmpObj1, T * tmpObj2)		{	obj.clear(); obj.push_back(tmpObj1); obj.push_back(tmpObj2);	};

	template <typename T>
	void InvariantMassCut<T>::addPointer(T * tmpObj) 								{	obj.push_back(tmpObj); 																				};

	template <typename T>
	void InvariantMassCut<T>::setPointer(std::vector< T * > tmpObj) 	{	obj.clear(); obj = tmpObj; 																			};

	template <typename T>
	void InvariantMassCut<T>::setCut(double mass_min_, double mass_max_) { mass_min = mass_min_; mass_max = mass_max_; };

	template <typename T>
	void InvariantMassCut<T>::setMinCut(double mass_min_) { mass_min = mass_min_; };

	template <typename T>
	void InvariantMassCut<T>::setMaxCut(double mass_max_) { mass_max = mass_max_; };

	template <typename T>
	bool InvariantMassCut<T>::getInternalDecision()
	{
		if (obj.size() == 0)
			return false;

		double sum = getDecisionValue();
		return (sum >= mass_min && sum <= mass_max);
	};

	template <typename T>
	double InvariantMassCut<T>::getDecisionValue()
	{
		RMLV sum;
		for (typename std::vector< T * >::iterator it = obj.begin(); it != obj.end(); it++)
			sum += (*it)->p4;
		return sum.mass();
	};
}

template class KappaTools::InvariantMassCut<KDataMuon>;
template class KappaTools::InvariantMassCut<KDataJet>;
template class KappaTools::InvariantMassCut<KDataPFJet>;
template class KappaTools::InvariantMassCut<KParton>;
