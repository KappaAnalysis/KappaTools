#ifndef KBalancePtCut_h
#define KBalancePtCut_h

#include "BaseCut.h"
#include "Kappa/DataFormats/interface/KLorentzVector.h"
#include "../Objects/Zmumu.h"

namespace KappaTools
{
	/*
		mode:
			0 - obj1.pt() - obj2.pt()
			1 - (obj1.pt() - obj2.pt()) / obj1.pt()
	*/
	template <typename T1, typename T2>
	class BalancePtCut : public BaseCut
	{
	private:
		std::vector<T1 *> obj1;
		std::vector<T2 *> obj2;
		unsigned int mode;
		double min;
		double max;
	public:
		BalancePtCut();
		void setPointer1(T1 * tmpObj);
		void setPointer2(T2 * tmpObj);
		void addPointer1(T1 * tmpObj);
		void addPointer2(T2 * tmpObj);

		void setMode(unsigned int mode_);

		void setCut(double cut_);
		void setMinCut(double min_);
		void setMaxCut(double max_);

		virtual bool getInternalDecision();

		double getDecisionValue();

		static const int AbsPtDiff = 0;
		static const int RelPtDiff = 1;
		static const int PtRatio = 2;
	};
}
#endif
