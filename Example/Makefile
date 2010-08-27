#------------------------------------------------------------------------------
PROGRAM  = test.bin test.sbin
#------------------------------------------------------------------------------

include ../Makefile.root

%.bin: %.o
	$(CXX) $(LDFLAGS) -lKToolbox -lKRootTools -lKappa -L../../Kappa/DataFormats/test/ -o $@ $^

%.sbin: %.o ../lib/libKToolbox.a ../lib/libKRootTools.a ../../Kappa/DataFormats/test/libKappa.o
	$(CXX) $(LDFLAGS) -o $@ $^
