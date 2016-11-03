cmake_minimum_required (VERSION 2.6)
project (KappaTools C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfatal-errors -std=c++0x -fpic -Wall -O2 -g") # -pedantic
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

# to compile with clang, use: cmake . -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_C_COMPILER=/usr/bin/clang

include(FindROOT.cmake)

if (DEFINED ENV{CMSSW_RELEASE_BASE})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTANDALONE")
	execute_process(WORKING_DIRECTORY $ENV{CMSSW_BASE} COMMAND scram tool info boost COMMAND grep "Version" COMMAND grep -E -o "[0-9.]*(-.*)?" COMMAND tr -d '\n' OUTPUT_VARIABLE BOOSTVER)
	set(BOOST_INCLUDE_DIR "/afs/cern.ch/cms/$ENV{SCRAM_ARCH}/external/boost/${BOOSTVER}/include/")
	set(BOOST_LIB_DIR "/afs/cern.ch/cms/$ENV{SCRAM_ARCH}/external/boost/${BOOSTVER}/lib/")
	set(CORRECTION_DIR "..")
	message(STATUS "Looking for boost ${BOOSTVER} inc in CMSSW: found ${BOOST_INCLUDE_DIR}")
	message(STATUS "Looking for boost ${BOOSTVER} lib in CMSSW: found ${BOOST_LIB_DIR}")
	FIND_LIBRARY(BOOST_REGEX
		NAMES boost_regex
		PATHS
		${BOOST_LIB_DIR}
		NO_DEFAULT_PATH
		)
else()
	FIND_LIBRARY(BOOST_REGEX
		NAMES boost_regex
		)
endif()

FIND_LIBRARY(KAPPA
	NAMES Kappa
	PATHS
	"$ENV{KAPPAPATH}"
	"../Kappa/lib"
	)

FIND_LIBRARY(ROOT_GENVECTOR
	NAMES GenVector
	PATHS
	${ROOT_LIBRARY_DIR}
	)


set(INCLUDE_DIRECTORIES
	${ROOT_INCLUDE_DIR}
	${BOOST_INCLUDE_DIR}
	${CORRECTION_DIR}
)

include_directories(SYSTEM ${INCLUDE_DIRECTORIES})
include_directories(${closure_SOURCE_DIR}../)


file(GLOB KToolbox_SRC "Toolbox/src/*.cpp")
add_library(KToolbox SHARED ${KToolbox_SRC})

file(GLOB KRootTools_SRC "RootTools/src/*.cpp")
add_library(KRootTools SHARED ${KRootTools_SRC})

file(GLOB KPlotTools_SRC "PlotTools/src/*.cpp")
add_library(KPlotTools SHARED ${KPlotTools_SRC})

# Needs C++ 11 standard
set_property(TARGET KRootTools PROPERTY CXX_STANDARD 11)
set_property(TARGET KRootTools PROPERTY CXX_STANDARD_REQUIRED ON)


add_executable(minimal Example/bin/minimal.cpp)
add_executable(minimal_disc Example/bin/minimal_disc.cpp)
add_executable(KappaTools_Example_test Example/test/test.cpp)
add_executable(KappaTools_Example_testMatching Example/test/testMatching.cpp)
add_executable(KappaTools_PlotTools_tests PlotTools/test/tests.cpp )
add_executable(KappaTools_PlotTools_tests1 PlotTools/test/tests1.cpp)
add_executable(example Toolbox/bin/example.cc)
add_executable(KappaTools_Toolbox_tests Toolbox/test/tests.cc)
add_executable(duplicateEventChecker Tools/bin/duplicateEventChecker.cc)
add_executable(triggerPrescale Tools/bin/triggerPrescale.cc)
add_executable(writeLSList Tools/bin/writeLSList.cc)
add_executable(xsec Tools/bin/xsec.cc)

target_link_libraries(minimal KToolbox KRootTools KPlotTools ${KAPPA} ${BOOST_REGEX} ${ROOT_LIBRARIES} ${ROOT_GENVECTOR})
target_link_libraries(minimal_disc KToolbox KRootTools KPlotTools ${KAPPA} ${BOOST_REGEX} ${ROOT_LIBRARIES} ${ROOT_GENVECTOR})
target_link_libraries(KappaTools_Example_test KToolbox KRootTools KPlotTools ${KAPPA} ${BOOST_REGEX} ${ROOT_LIBRARIES} ${ROOT_GENVECTOR})
target_link_libraries(KappaTools_Example_testMatching KToolbox KRootTools ${KAPPA} ${BOOST_REGEX} ${ROOT_LIBRARIES} ${ROOT_GENVECTOR})
target_link_libraries(KappaTools_PlotTools_tests KToolbox KRootTools KPlotTools ${BOOST_REGEX} ${ROOT_LIBRARIES} ${ROOT_GENVECTOR})
target_link_libraries(KappaTools_PlotTools_tests1 KRootTools KPlotTools KToolbox ${BOOST_REGEX} ${ROOT_LIBRARIES} ${ROOT_GENVECTOR})
target_link_libraries(example KToolbox ${BOOST_REGEX} ${ROOT_LIBRARIES} ${ROOT_GENVECTOR})
target_link_libraries(KappaTools_Toolbox_tests KToolbox ${BOOST_REGEX} ${ROOT_LIBRARIES} ${ROOT_GENVECTOR})
target_link_libraries(duplicateEventChecker KToolbox KRootTools ${KAPPA} ${BOOST_REGEX} ${ROOT_LIBRARIES} ${ROOT_GENVECTOR})
target_link_libraries(triggerPrescale KToolbox KRootTools ${BOOST_REGEX} ${ROOT_LIBRARIES} ${ROOT_GENVECTOR})
target_link_libraries(writeLSList KToolbox ${BOOST_REGEX} ${ROOT_LIBRARIES} ${ROOT_GENVECTOR})
target_link_libraries(xsec KToolbox KRootTools ${BOOST_REGEX} ${ROOT_LIBRARIES} ${ROOT_GENVECTOR})
