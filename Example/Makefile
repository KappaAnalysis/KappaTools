#------------------------------------------------------------------------------
PROGRAM  = test.ana
#------------------------------------------------------------------------------

include ../Makefile.root
LDFLAGS += -lKToolbox -lKRootTools -lKappa

%.ana: %.o
	$(CXX) $(LDFLAGS) -L../../Kappa/DataFormats/test/ -o $@ $^
