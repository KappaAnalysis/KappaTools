SHELL = /bin/sh

# get the correct root configuration
ROOTCFLAGS   := $(shell root-config --cflags) -I ../ -I ../../Kappa/ -I . -I ${MYBOOST}
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)


# set the compiler options
CXX           = g++
__CXXFLAGS__  = -fPIC -DPIC -ansi -Wall -Woverloaded-virtual -Wno-non-virtual-dtor -D_GNU_SOURCE $(ROOTCFLAGS)


%.o   : CXXFLAGS =    -O3 $(__CXXFLAGS__)
%.dbg : CXXFLAGS = -g -O0 $(__CXXFLAGS__) -DDEBUG

LIBS  = $(ROOTLIBS) $(SYSLIBS) # -lstdc++

# set the linker options
LD            = g++                #use g++ for linking
LDFLAGS       = -lMathCore -lGenVector -z muldefs
SOFLAGS       = -shared

#------------------------------------------------------------------------------

default : triggerTest
debug   :

all     : default

#------------------------------------------------------------------------------


%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

%.dbg: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

triggerTest: triggerTest.o TriggerTest.o ../RootTools/FileInterface.o ../../Kappa/DataFormats/test/libKappa.o ../RootTools/LumiMetadataProvider.o ../Toolbox/ProgressMonitor.o ../Toolbox/CmdLineSetup.o ../Toolbox/Version.o ../Toolbox/StringTools.o
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

.PHONY clean:
	@rm -f *.o *.dbg
	@rm -f 1KlickAna
	@rm -f *.o *.dbg
	@rm -f core.*

