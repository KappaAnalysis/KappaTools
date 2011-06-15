#------------------------------------------------------------------------------
BASEDIR ?= $(shell cd ..; pwd)
LIBFILES = libKRootTools.o FileInterface.o DisplayTools.o \
	Directory.o EventLogger.o LSWatcher.o RunLumiReader.o \
	$(BASEDIR)/../Kappa/DataFormats/test/KDebug.o
PROGRAM  = libKRootTools.so libKRootTools.a $(LIBFILES)
#------------------------------------------------------------------------------

include $(BASEDIR)/Makefile.root
