# @file Makefile
# @date 2019/01/11
# @brief 1ファイル1app用のMakefile. sample.cpp(main関数含む)を./sampleにする. TARGETに列挙すればいい
TARGET = mkinit

CXX = g++
CXXFLAGS = -O2 -W -Wall
CXXLIBS  = -lm -O3 -lCOMCLI

all : ${TARGET} 

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.C.o :
	${CXX} ${CXXFLAGS} -c $< -I.

.PHONY : clean
clean :
	@rm -f ${TARGET} *.o *~
