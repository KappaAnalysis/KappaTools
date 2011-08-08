#ifndef KAPPA_JETID_H
#define KAPPA_JETID_H

#include <Kappa/DataFormats/interface/KJetMET.h>

template<typename T>
struct JetIDLoose
{
	typedef const T &argument_type;
	bool operator()(const T &jet) const { return true; }
};

template<>
struct JetIDLoose<KDataJet>
{
	typedef const KDataJet &argument_type;
	bool operator()(const KDataJet &jet) const;
};

template<>
struct JetIDLoose<KDataPFJet>
{
	typedef const KDataPFJet &argument_type;
	bool operator()(const KDataPFJet &jet) const;
};

template<typename T>
bool jetIDTight(const T &jet);
template<>
bool jetIDTight(const KDataPFJet &jet);

#endif
