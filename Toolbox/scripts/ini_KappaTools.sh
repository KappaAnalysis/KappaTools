#!/bin/bash

# get path of KappaTools installation
if [[ ${BASH_SOURCE[0]} == *"${CMSSW_BASE}/bin/"* || ${BASH_SOURCE[0]} == *"${CMSSW_BASE}/src/KappaTools/"* ]]; then
	export KAPPATOOLSPATH=$CMSSW_BASE/src/KappaTools
else
	# get KappaTools dir relative to location of this script
	export KAPPATOOLSPATH=$(readlink -f $(dirname $(readlink -f ${BASH_SOURCE[0]}))/../..)
fi

export SCRAM_IGNORE_PACKAGES="KappaTools/Plots KappaTools/PythonTools"

export KAPPAPATH=$(readlink -f $KAPPATOOLSPATH/../Kappa)

# configurations needed for compilation of C++ code
#export BOOSTPATH=$(ls /afs/cern.ch/cms/${SCRAM_ARCH}/external/boost/* -d | tail -n 1)/
export LD_LIBRARY_PATH="$KAPPATOOLSPATH/lib:$KAPPAPATH/lib:$LD_LIBRARY_PATH"

