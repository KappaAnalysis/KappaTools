#------------------------------------------------------------------------------
LIBFILES = libKRootTools.o FileInterface.o LumiMetadataProvider.o DisplayTools.o \
	Directory.o EventLogger.o RunLumiReader.o
PROGRAM  = libKRootTools.so libKRootTools.a Matching.bin Matching.sbin $(LIBFILES)
#------------------------------------------------------------------------------

include ../Makefile.root

%.bin: %.o
	$(CXX) $(LDFLAGS) -lKToolbox -lKRootTools -lKappa -L../../Kappa/DataFormats/test/ -o $@ $^

%.sbin: %.o ../lib/libKToolbox.a ../lib/libKRootTools.a ../../Kappa/DataFormats/test/libKappa.a
	$(CXX) $(LDFLAGS) -o $@ $^
