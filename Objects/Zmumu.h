#ifndef KZmumuObjects_h
#define KZmumuObjects_h

#include "DataFormats/interface/KBasic.h"
#include "DataFormats/interface/KMuon.h"
#include "DataFormats/interface/KMetadata.h"
#include "DataFormats/interface/KLorentzVector.h"
#include "DataFormats/interface/KJetMET.h"
#include "Math/GenVector/VectorUtil.h"
#include "TMath.h"
#include <stdlib.h>

namespace KappaTools
{
	template <typename JetType, typename METType>
	class ZmumuObjects
	{
		private:
			void printMuonInformation(KDataMuon * muon);
			KDataMuon * muon1, * muon2;
			JetType * rjet;	// recoil jet
			METType * met;
			KEventMetadata * eventMetadata;
			KLumiMetadata * lumiMetadata;
			KDataVertex * primaryvertex;
			KDataBeamSpot * beamspot;
			void recalcP4();
		public:
			void printInformation();
			RMLV p4;
			RMLV getDiMuP4();
			RMLV getDiMu() { return getDiMuP4(); };

			void setMuons(KDataMuon * muon1, KDataMuon * muon2);
			void setRJet(JetType * rjet);
			void setMET(METType * met);
			void setMetadata(KEventMetadata * eventMetadata_, KLumiMetadata * lumiMetadata_);
			void setPV(KDataVertex * pv);
			void setBS(KDataBeamSpot * bs);

			double getDeltaPhi();
			double getResponse();

			KDataMuon * getMuon1();
			KDataMuon * getMuon2();
			JetType * getRJet();
			METType * getMET();
			KDataVertex * getPV();
			KDataBeamSpot * getBS();
			KEventMetadata * getEventMetadata();
			KLumiMetadata * getLumiMetadata();

			ZmumuObjects() : muon1(0), muon2(0), rjet(0), met(0), eventMetadata(0), primaryvertex(0), beamspot(0) {};
	};
}

#endif
