#------------------------------------------------------------------------------
LIBFILES = libKToolbox.o ProgressMonitor.o StringTools.o IOHelper.o Version.o CmdLineSetup.o
PROGRAM  = libKToolbox.so libKToolbox.a example.bin example.sbin $(LIBFILES)
#------------------------------------------------------------------------------

include ../Makefile.base
COPTS += -pedantic

%.bin: %.o
	$(CXX) $(LDFLAGS) -lKToolbox -o $@ $^

%.sbin: %.o libKToolbox.a
	$(CXX) $(LDFLAGS) -o $@ $^
