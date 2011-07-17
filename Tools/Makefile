#------------------------------------------------------------------------------
BASEDIR ?= $(shell cd ..; pwd)
PROGRAM  = triggerPrescale.sbin writeLSList.sbin duplicateEventChecker.sbin xsec.sbin
#------------------------------------------------------------------------------

include $(BASEDIR)/Makefile.root

%.sbin: %.o $(BASEDIR)/lib/libKRootTools.a $(BASEDIR)/../Kappa/DataFormats/test/libKappa.o $(BASEDIR)/lib/libKToolbox.a
	$(CXX) $(LDFLAGS) -o $@ $^
