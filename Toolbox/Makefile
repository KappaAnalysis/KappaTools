#------------------------------------------------------------------------------
BASEDIR ?= $(shell cd ..; pwd)
LIBFILES = $(subst cpp,o,$(shell ls *.cpp))
PROGRAM  = libKToolbox.so libKToolbox.a \
	$(subst cc,bin,$(shell ls *.cc)) $(subst cc,sbin,$(shell ls *.cc)) $(LIBFILES)
#------------------------------------------------------------------------------

include $(BASEDIR)/Makefile.base
COPTS += -pedantic

%.bin: %.o
	$(CXX) $(LDFLAGS) -lKToolbox -o $@ $^

%.sbin: %.o libKToolbox.a
	$(CXX) $(LDFLAGS) -o $@ $^
