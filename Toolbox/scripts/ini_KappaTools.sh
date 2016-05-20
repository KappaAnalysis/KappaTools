#!/bin/bash

if [ -n "$BASH_VERSION" ]; then

	# get path of KappaTools installation for bash
	if [[ ${BASH_SOURCE[0]} == *"${CMSSW_BASE}/bin/"* || ${BASH_SOURCE[0]} == *"${CMSSW_BASE}/src/KappaTools/"* ]]; then
		export KAPPATOOLSPATH=$CMSSW_BASE/src/KappaTools
	else
		# get KappaTools dir relative to location of this script for bash
		export KAPPATOOLSPATH=$(readlink -f $(dirname $(readlink -f ${BASH_SOURCE[0]}))/../..)
	fi

elif [ -n "$ZSH_VERSION" ]; then

	# get path of KappaTools installation for zsh
	if [[ ${0} == *"${CMSSW_BASE}/bin/"* || ${0} == *"${CMSSW_BASE}/src/KappaTools/"* ]]; then
		export KAPPATOOLSPATH=$CMSSW_BASE/src/KappaTools
	else
		# get KappaTools dir relative to location of this script for zsh
		export KAPPATOOLSPATH=$(readlink -f -- $(dirname  -- "$(readlink -f -- "${0}")")/../..)
	fi

fi

export KAPPAPATH=$(readlink -f $KAPPATOOLSPATH/../Kappa)

if [[ -z "${CMSSW_BASE}" ]] && [[ ${CMSSW_BASE}* == $(readlink -f .) ]];
then
	# configurations needed for compilation of C++ code
	#export BOOSTPATH=$(ls /afs/cern.ch/cms/${SCRAM_ARCH}/external/boost/* -d | tail -n 1)/
	export LD_LIBRARY_PATH="$KAPPATOOLSPATH/lib:$KAPPAPATH/lib:$LD_LIBRARY_PATH"
else
	cp $KAPPAPATH/DataFormats/test/kappa.xml $CMSSW_BASE/config/toolbox/${SCRAM_ARCH}/tools/selected/kappa.xml
	scram setup kappa
	if [ command -v symlinks > /dev/null 2>&1 ]; then
	    symlinks -c ${CMSSW_BASE}/external/${SCRAM_ARCH}/lib/ > /dev/null 2>&1
	else
	    for FILE in ${CMSSW_BASE}/external/${SCRAM_ARCH}/lib/*; do
	        if [ -L $FILE ]; then
                LINKPATH=$(readlink $FILE)
                rm -f $FILE
                ln -s ${LINKPATH/$CMSSW_BASE/..\/..\/..} $FILE
            fi
        done
    fi
fi
