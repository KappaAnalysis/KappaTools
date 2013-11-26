#------------------------------------------------------------------------------
BASEDIR ?= $(shell cd ..; pwd)
PROGRAM  = minimal.sbin minimal_disc.sbin
#------------------------------------------------------------------------------

include $(BASEDIR)/Makefile.root
#LDFLAGS  += -lHepMC -L$(BASEDIR)/external/hepmc/lib/
#CXXFLAGS += -I$(BASEDIR)/external/hepmc/include/

%.bin: %.o
	$(CXX) $(LDFLAGS) -lKToolbox -lKRootTools -lKappa -L$(BASEDIR)/../Kappa/DataFormats/test/ -o $@ $^

%.sbin: %.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(BASEDIR)/lib/libKRootTools.a $(BASEDIR)/lib/libKPlotTools.a $(BASEDIR)/../Kappa/DataFormats/test/libKappa.o $(BASEDIR)/lib/libKToolbox.a
