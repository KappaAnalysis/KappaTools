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


	NoneCut::NoneCut() : BaseCut("none cut"), dec(true) {}

	NoneCut::NoneCut(bool dec_) : BaseCut("none cut"), dec(dec_) {}

	void NoneCut::setCut(bool dec_)
	{
		dec=dec_;
	}

	bool NoneCut::getInternalDecision()
	{
		return dec;
	}

	double NoneCut::getDecisionValue()
	{
		return (dec ? 1. : 0.);
	}
}
#endif
