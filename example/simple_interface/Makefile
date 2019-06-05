# @file Makefile
# @date 2019/01/11
# @brief 1ファイル1app用のMakefile. sample.cpp(main関数含む)を./sampleにする. TARGETに列挙すればいい
TARGET = clitest

ROOTCFLAGS = `root-config --cflags`
ROOTGLIBS  = `root-config --libs`

CXX = g++-9
CXXFLAGS = -W -Wall
CXXLIBS = -lm -lCOMCLI

all : ${TARGET} 

%: %.cpp
	$(CXX) $(CXXFLAGS) $(CXXLIBS) $< -o $@

.C.o :
	${CXX} ${CXXFLAGS} -c $< -I.

.PHONY : clean
clean :
	@rm -f ${TARGET} *.o *~ app*
