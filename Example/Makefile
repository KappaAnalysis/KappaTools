#------------------------------------------------------------------------------
BASEDIR ?= $(shell cd ..; pwd)
PROGRAM  = test.bin test.sbin testMatching.bin testMatching.sbin
#------------------------------------------------------------------------------

include $(BASEDIR)/Makefile.root

%.bin: %.o
	$(CXX) $(LDFLAGS) -lKToolbox -lKRootTools -lKappa -L$(BASEDIR)/../Kappa/DataFormats/test/ -o $@ $^

%.sbin: %.o $(BASEDIR)/lib/libKToolbox.a $(BASEDIR)/lib/libKRootTools.a $(BASEDIR)/../Kappa/DataFormats/test/libKappa.o
	$(CXX) $(LDFLAGS) -o $@ $^
