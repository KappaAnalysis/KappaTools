CUTS=./Cuts
OBJECTS=./Objects
PLOTS=./Plots
TOOLS=./Tools

# command for documentation generation
DOXYGEN=doxygen

.PHONY: all clean

all:
	$(MAKE) -C $(CUTS)
	$(MAKE) -C $(OBJECTS)
	$(MAKE) -C $(PLOTS)
	$(MAKE) -C $(TOOLS)

clean:

	$(MAKE) -C $(CUTS) clean
	$(MAKE) -C $(OBJECTS) clean
	$(MAKE) -C $(PLOTS) clean
	$(MAKE) -C $(TOOLS) clean

# if one day we want to...
# doc:
# 	$(DOXYGEN) scripts/Doxygen.cfg