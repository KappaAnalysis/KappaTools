#------------------------------------------------------------------------------
PROGRAM  = test.ana
#------------------------------------------------------------------------------

include ../Makefile.root
LDFLAGS += -lKToolbox -lKRootTools

%.ana: %.o ../../Kappa/DataFormats/test/dict.so
	$(LD) $(LDFLAGS) -o $@ $^
