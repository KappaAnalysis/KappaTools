#ifndef KNoneCut_h
#define KNoneCut_h

#include "BaseCut.h"

namespace KappaTools
{
	// this cut does nothing except return true (default) or false
	// it's useful as first cut or as a place holder
	class NoneCut : public BaseCut
	{
	private:
		bool dec;
	public:
		NoneCut();
		NoneCut(bool dec_);
		void setCut(bool dec_);
		virtual bool getInternalDecision();
		double getDecisionValue();
	};
}
#endif
