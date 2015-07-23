#------------------------------------------------------------------------------
BASEDIR ?= $(shell cd ..; pwd)
LIBFILES = Binning.o BookPlots.o PlotInterface.o Plot_Run.o
PROGRAM  = libKPlotTools.so libKPlotTools.a tests.sbin tests1.sbin $(LIBFILES)
#------------------------------------------------------------------------------

include $(BASEDIR)/Makefile.root

%.sbin: %.o libKPlotTools.a
	$(CXX) -o $@ $^ \
	$(BASEDIR)/lib/libKRootTools.a $(BASEDIR)/../Kappa/DataFormats/test/libKappa.a $(BASEDIR)/lib/libKToolbox.a $(LDFLAGS) 
