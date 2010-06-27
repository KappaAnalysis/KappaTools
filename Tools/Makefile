#------------------------------------------------------------------------------
PROGRAM  = triggerTest.sbin
#------------------------------------------------------------------------------

include ../Makefile.root

triggerTest.sbin: triggerTest.o TriggerTest.o ../lib/libKToolbox.a ../lib/libKRootTools.a ../../Kappa/DataFormats/test/libKappa.o
	$(CXX) $(LDFLAGS) -o $@ $^
