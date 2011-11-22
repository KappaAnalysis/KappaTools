#------------------------------------------------------------------------------
BASEDIR ?= $(shell cd ..; pwd)
LIBFILES = libKRootTools.o FileInterface.o FileInterfaceBase.o DisplayTools.o \
	Directory.o EventLogger.o HLTTools.o JetID.o JECTools.o LSWatcher.o LumiCounter.o RunLumiReader.o \
	$(BASEDIR)/../Kappa/DataFormats/test/KDebug.o
PROGRAM  = libKRootTools.so libKRootTools.a $(LIBFILES)
#------------------------------------------------------------------------------

include $(BASEDIR)/Makefile.root
