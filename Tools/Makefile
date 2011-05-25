#------------------------------------------------------------------------------
PROGRAM  = triggerPrescale.sbin writeLSList.sbin duplicateEventChecker.sbin xsec.sbin
#------------------------------------------------------------------------------

include ../Makefile.root

%.sbin: %.o ../lib/libKRootTools.a ../../Kappa/DataFormats/test/libKappa.o ../lib/libKToolbox.a
	$(CXX) $(LDFLAGS) -o $@ $^
