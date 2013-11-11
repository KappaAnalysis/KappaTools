SUBDIR = boost

all: $(SUBDIR) libupdate

BOOSTVER = 1_44_0

boost:
	ln -s $(shell ls /afs/cern.ch/cms/${SCRAM_ARCH}/external/boost/* -d | tail -n 1)/include/boost
	ln -s $(shell ls /afs/cern.ch/cms/${SCRAM_ARCH}/external/boost/* -d | tail -n 1)/lib

libupdate:

install:

clean:
	rm -f boost
	rm -f lib