#------------------------------------------------------------------------------
BASEDIR ?= $(shell cd ..; pwd)
PROGRAM  = triggerPrescale.sbin writeLSList.sbin duplicateEventChecker.sbin xsec.sbin
#------------------------------------------------------------------------------

include $(BASEDIR)/Makefile.root

%.sbin: %.o
	$(CXX) -o $@ $^ $(BASEDIR)/lib/libKRootTools.a $(BASEDIR)/../Kappa/DataFormats/test/libKappa.a $(BASEDIR)/lib/libKToolbox.a $(LDFLAGS) 
