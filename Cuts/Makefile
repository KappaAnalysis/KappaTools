SHELL = /bin/sh

# get the correct root configuration
ROOTCFLAGS   := $(shell root-config --cflags) -I ../../Kappa/ #-I ${CMSSW_BASE}/src/ -I ${CMSSW_RELEASE_BASE}/src/
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)

# set the compiler options
CXX           = g++
__CXXFLAGS__  = -fPIC -DPIC -ansi -Wall -Woverloaded-virtual -Wno-non-virtual-dtor -D_GNU_SOURCE $(ROOTCFLAGS)

%.o   : CXXFLAGS =    -O3 $(__CXXFLAGS__)
%.dbg : CXXFLAGS = -g -O0 $(__CXXFLAGS__) -DDEBUG

                                   #-g compile with debug information
                                   #-O optimize
                                   #-Wall show warnings for everything
                                   #-fPIC compile source file as sharable object

LIBS  = $(ROOTLIBS) $(SYSLIBS) # -lstdc++

# set the linker options
LD            = g++                #use g++ for linking
LDFLAGS       = -lMathCore #-lGenVector -lRooFit -lMinuit
SOFLAGS       = -shared

#------------------------------------------------------------------------------
#------------------------------------------------------------------------------

#include "VertexNdofCut.h"
#include "BalancePhiCut.h"
#include "BalancePtCut.h"
#include "MuonTypeCut.h"
#include "IsolationCut.h"

default : BaseCut.o CutFlow.o NoneCut.o PtCut.o EtaCut.o DeltaRCut.o ChargeCut.o ExistenceCut.o CutGroup.o InvariantMassCut.o L1TriggerCut.o HLTriggerCut.o GoodTracksFractionCut.o METoverSumEtCut.o VertexNdofCut.o BalancePhiCut.o BalancePtCut.o MuonTypeCut.o IsolationCut.o EventFilterCut.o
debug   :

all     : default

#------------------------------------------------------------------------------
#------------------------------------------------------------------------------

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

%.dbg: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

.PHONY clean:
	@rm -f *.o *.dbg
	@rm -f core.*

