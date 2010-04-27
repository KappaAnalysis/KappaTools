#------------------------------------------------------------------------------
LIBFILES = libKToolbox.o ProgressMonitor.o StringTools.o Version.o
PROGRAM  = libKToolbox.so libKToolbox.a example.bin example.sbin $(LIBFILES)
#------------------------------------------------------------------------------

include ../Makefile.base
COPTS += -pedantic

%.bin: %.o
	$(LD) $(LDFLAGS) -lKToolbox -o $@ $^

%.sbin: %.o libKToolbox.a
	$(LD) $(LDFLAGS) -o $@ $^
