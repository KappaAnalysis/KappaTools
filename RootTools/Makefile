#------------------------------------------------------------------------------
BASEDIR ?= $(shell cd ..; pwd)
LIBFILES = $(subst cpp,o,*.cpp) \
	$(BASEDIR)/../Kappa/DataFormats/test/KDebug.o
PROGRAM  = libKRootTools.so libKRootTools.a $(LIBFILES)
#------------------------------------------------------------------------------

include $(BASEDIR)/Makefile.root
