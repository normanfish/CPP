CXX = g++
CXXFLAGS = -Wextra -Wall -Wvla -std=c++14 -g
files = ikea.cpp IkeaStoreItem.h IkeaStoreItem.cpp ItemSpecifier.h ItemSpecifier.cpp Reader.h Reader.cpp

all: $(files) 
	$(CXX) $(CXXFLAGS) -o ex2 $(files)

clean:
	rm -f *.o ex2
