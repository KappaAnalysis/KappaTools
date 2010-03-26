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

#default : BasePlots.o StandardPlots.o MuonPlots.o TauPlots.o ZtautauMuJetPlots.o JetPlots.o
default : BasePlot.o StandardP4Plots.o
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



