#------------------------------------------------------------------------------
PROGRAM  = triggerTest.sbin
#------------------------------------------------------------------------------

include ../Makefile.root

triggerPrescale.sbin: triggerPrescale.o ../lib/libKToolbox.a ../lib/libKRootTools.a ../../Kappa/DataFormats/test/libKappa.o
	$(CXX) $(LDFLAGS) -o $@ $^
