SUBDIR = boost

all: $(SUBDIR) libupdate

BOOSTVER = 1_44_0

boost:
	wget http://switch.dl.sourceforge.net/project/boost/boost/1.44.0/boost_$(BOOSTVER).tar.bz2 -O boost.tar.bz2
	tar -xvjf boost.tar.bz2
	rm boost.tar.bz2
	ln -fs boost_$(BOOSTVER)/boost boost

libupdate:

install:

clean:
