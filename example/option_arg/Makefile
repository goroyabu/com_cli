# @file Makefile
# @date 2019/01/11
# @brief 1ファイル1app用のMakefile. sample.cpp(main関数含む)を./sampleにする. TARGETに列挙すればいい
TARGET = test test2

CXX_DEBUG_FLAGS = -pg -O0
CXX_RELEASE_FLAGS = -s -O2

FLAGS = -I${INCLUDEPATH}

ROOTCFLAGS = `root-config --cflags`
ROOTGLIBS  = `root-config --libs`
LIBS = -lm -lfftw3 -O3 -lCOMCLI

CXX = g++
CXXFLAGS = -O2 -W -Wall ${ROOTCFLAGS} ${FLAGS}
CXXLIBS = ${ROOTGLIBS} ${LIBS}

.PHONY : release
release : CXXFLAGS += ${CXX_RELEASE_FLAGS}
release : all
.PHONY : debug
debug : CXXFLAGS += ${CXX_DEBUG_FLAGS}
debug : all

all : ${TARGET} 

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.C.o :
	${CXX} ${CXXFLAGS} -c $< -I.

.PHONY : clean
clean :
	@rm -f ${TARGET} *.o *~ app*
