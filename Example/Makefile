#------------------------------------------------------------------------------
BASEDIR ?= $(shell cd ..; pwd)
PROGRAM  = minimal.sbin minimal_disc.sbin
#------------------------------------------------------------------------------

include $(BASEDIR)/Makefile.root
#LDFLAGS  += -lHepMC -L$(BASEDIR)/external/hepmc/lib/
#CXXFLAGS += -I$(BASEDIR)/external/hepmc/include/

%.bin: %.o
	$(CXX) $^ -o $@ -lKappa -lKToolbox -lKRootTools -L$(BASEDIR)/../Kappa/DataFormats/test/ $(LDFLAGS)

%.sbin: %.o
	$(CXX) $^ -o $@  $(BASEDIR)/lib/libKRootTools.a $(BASEDIR)/lib/libKPlotTools.a $(BASEDIR)/../Kappa/DataFormats/test/libKappa.a $(BASEDIR)/lib/libKToolbox.a $(LDFLAGS)
