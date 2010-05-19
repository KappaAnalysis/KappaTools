#------------------------------------------------------------------------------
PROGRAM  = test.bin test.sbin
#------------------------------------------------------------------------------

include ../Makefile.root

%.bin: test.o
	$(CXX) $(LDFLAGS) -lKToolbox -lKRootTools -lKappa -L../../Kappa/DataFormats/test/ -o $@ $^

%.sbin: test.o ../lib/libKToolbox.a ../lib/libKRootTools.a ../../Kappa/DataFormats/test/libKappa.o
	$(CXX) $(LDFLAGS) -o $@ $^
