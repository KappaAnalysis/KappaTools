#ifndef KChargeCut_h
#define KChargeCut_h

#include "BaseCut.h"
#include <vector>
#include <algorithm>
#include "DataFormats/interface/KMuon.h"

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
}
#endif
