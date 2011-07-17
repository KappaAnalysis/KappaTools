#ifndef KMuonQualityCut_h
#define KMuonQualityCut_h

#include "BaseCut.h"
#include "Kappa/DataFormats/interface/KMuon.h"

namespace KappaTools
{
	class MuonQualityCut : public BaseCut
	{
	private:
		KDataMuon * obj;
		unsigned int type;
	public:
		enum SelectionType
		{
			All = (unsigned int)1 << 0,                      // dummy options - always true
			AllGlobalMuons = (unsigned int)1 << 1,           // checks isGlobalMuon flag
			AllStandAloneMuons = (unsigned int)1 << 2,       // checks isStandAloneMuon flag
			AllTrackerMuons = (unsigned int)1 << 3,          // checks isTrackerMuon flag
			TrackerMuonArbitrated = (unsigned int)1 << 4,    // resolve ambiguity of sharing segments
			AllArbitrated = (unsigned int)1 << 5,            // all muons with the tracker muon arbitrated
			GlobalMuonPromptTight = (unsigned int)1 << 6,    // global muons with tighter fit requirements
			TMLastStationLoose = (unsigned int)1 << 7,       // penetration depth loose selector
			TMLastStationTight = (unsigned int)1 << 8,       // penetration depth tight selector
			TM2DCompatibilityLoose = (unsigned int)1 << 9,   // likelihood based loose selector
			TM2DCompatibilityTight = (unsigned int)1 << 10,  // likelihood based tight selector
			TMOneStationLoose = (unsigned int)1 << 11,       // require one well matched segment
			TMOneStationTight = (unsigned int)1 << 12,       // require one well matched segment
			TMLastStationOptimizedLowPtLoose = (unsigned int)1 << 13, // combination of TMLastStation and TMOneStation
			TMLastStationOptimizedLowPtTight = (unsigned int)1 << 14, // combination of TMLastStation and TMOneStation
			GMTkChiCompatibility = (unsigned int)1 << 15,    // require tk stub have good chi2 relative to glb track
			GMStaChiCompatibility = (unsigned int)1 << 16,   // require sta stub have good chi2 compatibility relative to glb track
			GMTkKinkTight = (unsigned int)1 << 17,           // require a small kink value in the tracker stub
			TMLastStationAngLoose = (unsigned int)1 << 18,   // TMLastStationLoose with additional angular cuts
			TMLastStationAngTight = (unsigned int)1 << 19,   // TMLastStationTight with additional angular cuts
			TMOneStationAngLoose = (unsigned int)1 << 20,    // TMOneStationLoose with additional angular cuts
			TMOneStationAngTight = (unsigned int)1 << 21,    // TMOneStationTight with additional angular cuts
			// The two algorithms that follow are identical to what were known as
			// TMLastStationOptimizedLowPt* (sans the Barrel) as late as revision
			// 1.7 of this file. The names were changed because indeed the low pt
			// optimization applies only to the barrel region, whereas the sel-
			// ectors above are more efficient at low pt in the endcaps, which is
			// what we feel is more suggestive of the algorithm name. This will be
			// less confusing for future generations of CMS members, I hope...
			TMLastStationOptimizedBarrelLowPtLoose = (unsigned int)1 << 22, // combination of TMLastStation and TMOneStation but with low pT optimization in barrel only
			TMLastStationOptimizedBarrelLowPtTight = (unsigned int)1 << 23  // combination of TMLastStation and TMOneStation but with low pT optimization in barrel only
		};

		MuonQualityCut();
		MuonQualityCut(KDataMuon * tempObj);
		MuonQualityCut(unsigned int type_);

		void setType(unsigned int type);
		void setPointer(KDataMuon * tmpObj);

		bool getInternalDecision();
		double getDecisionValue();
	};
}

#endif

