#------------------------------------------------------------------------------
BASEDIR ?= $(shell cd ..; pwd)
LIBFILES = libKPythonTools.o Config.o
PROGRAM  = libKPythonTools.so libKPythonTools.a test.bin $(LIBFILES)
#------------------------------------------------------------------------------

include $(BASEDIR)/Makefile.base

CXXFLAGS += -I /usr/include/python2.7
LDFLAGS += -lboost_python -lpython2.7 -lKToolbox

%.bin: %.o
	$(CXX) $(LDFLAGS) -lKToolbox -lKPythonTools -o $@ $^

%.sbin: %.o libKToolbox.a libKPythonTools.a
	$(CXX) $(LDFLAGS) -o $@ $^
