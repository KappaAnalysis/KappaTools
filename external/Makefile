SUBDIR = boost

all: $(SUBDIR)

boost:
	wget http://switch.dl.sourceforge.net/project/boost/boost/1.43.0/boost_1_43_0.tar.bz2 -O boost.tar.bz2
	tar -xvjf boost.tar.bz2
	rm boost.tar.bz2
	ln -fs boost_1_43_0/boost boost
