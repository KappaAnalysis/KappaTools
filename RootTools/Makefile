#------------------------------------------------------------------------------
LIBFILES = libKRootTools.o FileInterface.o LumiMetadataProvider.o DisplayTools.o \
	Directory.o EventLogger.o RunLumiReader.o ../../Kappa/DataFormats/test/KDebug.o
PROGRAM  = libKRootTools.so libKRootTools.a Matching.bin Matching.sbin $(LIBFILES)
#------------------------------------------------------------------------------

include ../Makefile.root

%.bin: %.o
	$(CXX) $(LDFLAGS) -lKToolbox -lKRootTools -lKappa -L../../Kappa/DataFormats/test/ -o $@ $^

%.sbin: %.o ../lib/libKToolbox.a libKRootTools.a ../../Kappa/DataFormats/test/libKappa.a
	$(CXX) $(LDFLAGS) -o $@ $^
