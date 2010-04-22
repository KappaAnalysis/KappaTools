#------------------------------------------------------------------------------
PROGRAM  = libKToolbox.so libKToolbox.a example.bin example.sbin
LIBFILES = libKToolbox.o ProgressMonitor.o StringTools.o
#------------------------------------------------------------------------------

include ../Makefile.base
COPTS += -pedantic

%.bin: %.o
	$(LD) $(LDFLAGS) -lToolbox -o $@ $^

%.sbin: %.o libKToolbox.a
	$(LD) $(LDFLAGS) -o $@ $^
