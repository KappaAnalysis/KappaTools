#------------------------------------------------------------------------------
BASEDIR ?= $(shell cd ..; pwd)
LIBFILES = libKToolbox.o ProgressMonitor.o StringTools.o IOHelper.o Version.o CmdLineSetup.o
PROGRAM  = libKToolbox.so libKToolbox.a example.bin example.sbin $(LIBFILES)
#------------------------------------------------------------------------------

include $(BASEDIR)/Makefile.root
COPTS += -pedantic

%.bin: %.o
	$(CXX) $(LDFLAGS) -lKToolbox -o $@ $^

%.sbin: %.o libKToolbox.a
	$(CXX) $(LDFLAGS) -o $@ $^
