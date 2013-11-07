#------------------------------------------------------------------------------
BASEDIR ?= $(shell cd ..; pwd)
LIBFILES = Binning.o BookPlots.o PlotInterface.o Plot_Run.o
PROGRAM  = libPlotTools.so libPlotTools.a tests.sbin tests1.sbin $(LIBFILES)
#------------------------------------------------------------------------------

include $(BASEDIR)/Makefile.root

%.sbin: %.o
	$(CXX) $(LDFLAGS) -lPlotTools -o $@ $^ \
	$(BASEDIR)/lib/libKRootTools.a $(BASEDIR)/../Kappa/DataFormats/test/libKappa.o $(BASEDIR)/lib/libKToolbox.a
