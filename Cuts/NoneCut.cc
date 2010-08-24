#include "NoneCut.h"

namespace KappaTools
{
	NoneCut::NoneCut() : BaseCut("none cut"), dec(true) {}

	NoneCut::NoneCut(bool dec_) : BaseCut("none cut"), dec(dec_) {}

	void NoneCut::setCut(bool dec_)
	{
		dec = dec_;
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
