#------------------------------------------------------------------------------
BASEDIR ?= $(shell cd ..; pwd)
LIBFILES = libKPythonTools.o Config.o
PROGRAM  = libKPythonTools.so libKPythonTools.a test.bin $(LIBFILES)
#------------------------------------------------------------------------------

include $(BASEDIR)/Makefile.base

CXXFLAGS += $(shell python-config --includes)
LDFLAGS += -lboost_python $(shell python-config --libs) -lKToolbox

%.bin: %.o
	$(CXX) $(LDFLAGS) -lKToolbox -lKPythonTools -o $@ $^

%.sbin: %.o libKToolbox.a libKPythonTools.a
	$(CXX) $(LDFLAGS) -o $@ $^
