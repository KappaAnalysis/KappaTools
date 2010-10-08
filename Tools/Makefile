#------------------------------------------------------------------------------
PROGRAM  = triggerPrescale.sbin writeLSList.sbin duplicateEventChecker.sbin
#------------------------------------------------------------------------------

include ../Makefile.root

%.sbin: %.o ../lib/libKToolbox.a ../lib/libKRootTools.a ../../Kappa/DataFormats/test/libKappa.o
	$(CXX) $(LDFLAGS) -o $@ $^
