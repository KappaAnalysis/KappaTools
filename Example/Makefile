#------------------------------------------------------------------------------
PROGRAM  = test.ana
#------------------------------------------------------------------------------

include ../Makefile.root
LDFLAGS += -lKToolbox -lKRootTools -lKappa

%.ana: %.o
	$(LD) $(LDFLAGS) -L../../Kappa/DataFormats/test/ -o $@ $^
