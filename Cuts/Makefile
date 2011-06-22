#------------------------------------------------------------------------------
BASEDIR ?= $(shell cd ..; pwd)
LIBFILES = BalancePhiCut.o BalancePtCut.o BaseCut.o ChargeCut.o CutFlow.o \
	CutGroup.o DeltaRCut.o EtaCut.o EventFilterCut.o ExistenceCut.o \
	GoodTracksFractionCut.o HLTriggerCut.o InvariantMassCut.o IsolationCut.o \
	L1TriggerCut.o METoverSumEtCut.o MuonHLTCut.o MuonMatchesCut.o \
	MuonQualityCut.o MuonTypeCut.o NoneCut.o NonFakeVertexCut.o PtCut.o \
	RhoVertexCut.o TauDiscrCut.o TrackChi2Cut.o TrackHitsCut.o TrackIPCut.o \
	TrackQualityCut.o UserBitFlagsCut.o VertexNdofCut.o zVertexCut.o
PROGRAM  = libKCuts.so libKCuts.a $(LIBFILES)
#------------------------------------------------------------------------------

include $(BASEDIR)/Makefile.root

LDFLAGS += -lboost_regex
