#------------------------------------------------------------------------------
BASEDIR ?= $(shell cd ..; pwd)
PROGRAM  = test.bin test.sbin testMatching.bin testMatching.sbin
#------------------------------------------------------------------------------

include $(BASEDIR)/Makefile.root

%.bin: %.o
	$(CXX) $(LDFLAGS) -lKToolbox -lKRootTools -lKappa -L$(BASEDIR)/../Kappa/DataFormats/test/ -o $@ $^

%.sbin: %.o $(BASEDIR)/lib/libKRootTools.a $(BASEDIR)/../Kappa/DataFormats/test/libKappa.o $(BASEDIR)/lib/libKToolbox.a
	$(CXX) $(LDFLAGS) -o $@ $^
