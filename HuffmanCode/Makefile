# use g++ with C++11 support
CXX=g++
CXXFLAGS?=-Wall -pedantic -g -O0 -std=c++11
OUTFILES=compress uncompress

all: $(OUTFILES)

compress:  compress.cpp Helper.cpp HCTree.cpp Helper.hpp HCTree.hpp test.cpp
	$(CXX) $(CXXFLAGS) -o compress compress.cpp Helper.cpp HCTree.cpp test.cpp

uncompress: uncompress.cpp uncompress.hpp Helper.cpp HCTree.cpp Helper.hpp HCTree.hpp test2.cpp
	$(CXX) $(CXXFLAGS) -o uncompress uncompress.cpp Helper.cpp HCTree.cpp test2.cpp

clean:
	rm -f $(OUTFILES) *.o

