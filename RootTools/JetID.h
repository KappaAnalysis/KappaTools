#ifndef KAPPA_JETID_H
#define KAPPA_JETID_H

#include <Kappa/DataFormats/interface/KJetMET.h>

template<typename T>
bool jetIDLoose(const T &jet)
{
	return true;
}

template<>
bool jetIDLoose(const class KDataJet &jet);

#endif
