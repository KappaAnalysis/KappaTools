cmake_minimum_required (VERSION 2.6)
project (KappaTools)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfatal-errors -std=c++0x -fpic -Wall -O2 -g") # -pedantic
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

# to compile with clang, use: cmake . -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_C_COMPILER=/usr/bin/clang

# Kappa
set(KAPPAPATH "$ENV{KAPPAPATH}")

# Load some basic macros which are needed later on
include(FindROOT.cmake)

if (DEFINED ENV{CMSSW_RELEASE_BASE})
	set(USE_BOOST_CMSSW TRUE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTANDALONE")
	execute_process(WORKING_DIRECTORY $ENV{CMSSW_BASE} COMMAND scram tool info boost COMMAND grep "Version" COMMAND grep -E -o "[0-9.]*(-.*)?" COMMAND tr -d '\n' OUTPUT_VARIABLE BOOSTVER)
	set(BOOST_INCLUDE_DIR "/afs/cern.ch/cms/$ENV{SCRAM_ARCH}/external/boost/${BOOSTVER}/include/")
	set(BOOST_LIB_DIR "/afs/cern.ch/cms/$ENV{SCRAM_ARCH}/external/boost/${BOOSTVER}/lib/")
	set(CORRECTION_DIR "..")
	message(STATUS "Looking for boost ${BOOSTVER} inc in CMSSW: found ${BOOST_INCLUDE_DIR}")
	message(STATUS "Looking for boost ${BOOSTVER} lib in CMSSW: found ${BOOST_LIB_DIR}")
else()
	set(USE_BOOST_CMSSW FALSE)
	set(BOOST_INCLUDE_DIR "")
	set(BOOST_LIB_DIR "")
	set(CORRECTION_DIR "")
	message("Expecting boost to be provided by system")
endif()

set(INCLUDE_DIRECTORIES
	${ROOT_INCLUDE_DIR}
	${BOOST_INCLUDE_DIR}
	${CORRECTION_DIR}
)

include_directories(SYSTEM ${INCLUDE_DIRECTORIES})
include_directories(${closure_SOURCE_DIR}../)

add_library(KToolbox SHARED
	Toolbox/src/CmdLineSetup.cpp
	Toolbox/src/IOHelper.cpp
	Toolbox/src/libKToolbox.cpp
	Toolbox/src/Math.cpp
	Toolbox/src/ProgressMonitor.cpp
	Toolbox/src/String.cpp
	Toolbox/src/StringTools.cpp
	Toolbox/src/Vector.cpp
	Toolbox/src/VectorTools.cpp
)

add_library(KRootTools SHARED
	RootTools/src/BranchHolder.cpp
	RootTools/src/Directory.cpp
	RootTools/src/DisplayTools.cpp
	RootTools/src/EventLogger.cpp
	RootTools/src/FileInterface.cpp
	RootTools/src/FileInterface2.cpp
	RootTools/src/FileInterfaceBase.cpp
	RootTools/src/HLTTools.cpp
	RootTools/src/JECTools.cpp
	RootTools/src/JetID.cpp
	RootTools/src/libKRootTools.cpp
	RootTools/src/LSWatcher.cpp
	RootTools/src/LumiCounter.cpp
	RootTools/src/PUReweighter.cpp
	RootTools/src/RunLumiReader.cpp
)

add_library(KPlotTools SHARED
	PlotTools/src/Binning.cpp
	PlotTools/src/BookPlots.cpp
	PlotTools/src/PlotInterface.cpp
	PlotTools/src/Plot_Run.cpp
)


add_executable(minimal
	Example/bin/minimal.cpp
)

add_executable(minimal_disc
	Example/bin/minimal_disc.cpp
)

add_executable(KappaTools_Example_test
	Example/test/test.cpp
)

add_executable(KappaTools_Example_testMatching
	Example/test/testMatching.cpp
)

add_executable(KappaTools_PlotTools_tests
	PlotTools/test/tests.cpp
)

add_executable(KappaTools_PlotTools_tests1
	PlotTools/test/tests1.cpp
)

add_executable(example
	Toolbox/bin/example.cc
)

add_executable(KappaTools_Toolbox_tests
	Toolbox/test/tests.cc
)

add_executable(duplicateEventChecker
	Tools/bin/duplicateEventChecker.cc
)

add_executable(triggerPrescale
	Tools/bin/triggerPrescale.cc
)

add_executable(writeLSList
	Tools/bin/writeLSList.cc
)

add_executable(xsec
	Tools/bin/xsec.cc
)


if (USE_BOOST_CMSSW)
	target_link_libraries(minimal
		KToolbox
		KRootTools
		KPlotTools
		-L${KAPPAPATH}/lib -lKappa
		-L${BOOST_LIB_DIR}
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(minimal_disc
		KToolbox
		KRootTools
		KPlotTools
		-L${KAPPAPATH}/lib -lKappa
		-L${BOOST_LIB_DIR}
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(KappaTools_Example_test
		KToolbox
		KRootTools
		-L${KAPPAPATH}/lib -lKappa
		-L${BOOST_LIB_DIR}
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(KappaTools_Example_testMatching
		KToolbox
		KRootTools
		-L${KAPPAPATH}/lib -lKappa
		-L${BOOST_LIB_DIR}
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(KappaTools_PlotTools_tests
		KToolbox
		KRootTools
		KPlotTools
		-L${BOOST_LIB_DIR}
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(KappaTools_PlotTools_tests1
		KToolbox
		KRootTools
		KPlotTools
		-L${BOOST_LIB_DIR}
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(example
		KToolbox
		-L${BOOST_LIB_DIR}
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(KappaTools_Toolbox_tests
		KToolbox
		-L${BOOST_LIB_DIR}
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(duplicateEventChecker
		KToolbox
		KRootTools
		-L${KAPPAPATH}/lib -lKappa
		-L${BOOST_LIB_DIR}
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(triggerPrescale
		KToolbox
		KRootTools
		-L${BOOST_LIB_DIR}
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(writeLSList
		KToolbox
		-L${BOOST_LIB_DIR}
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(xsec
		KToolbox
		KRootTools
		-L${BOOST_LIB_DIR}
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
else()
	target_link_libraries(minimal
		KToolbox
		KRootTools
		KPlotTools
		-L${KAPPAPATH}/lib -lKappa
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(minimal_disc
		KToolbox
		KRootTools
		KPlotTools
		-L${KAPPAPATH}/lib -lKappa
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(KappaTools_Example_test
		KToolbox
		KRootTools
		-L${KAPPAPATH}/lib -lKappa
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(KappaTools_Example_testMatching
		KToolbox
		KRootTools
		-L${KAPPAPATH}/lib -lKappa
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(KappaTools_PlotTools_tests
		KToolbox
		KRootTools
		KPlotTools
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(KappaTools_PlotTools_tests1
		KToolbox
		KRootTools
		KPlotTools
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(example
		KToolbox
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(KappaTools_Toolbox_tests
		KToolbox
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(duplicateEventChecker
		KToolbox
		KRootTools
		-L${KAPPAPATH}/lib -lKappa
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(triggerPrescale
		KToolbox
		KRootTools
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(writeLSList
		KToolbox
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
	
	target_link_libraries(xsec
		KToolbox
		KRootTools
		boost_regex
		${ROOT_LIBRARIES} -lGenVector
	)
endif()

