CXX = g++
CXXFLAGS = -Wextra -Wall -Wvla -std=c++14 -g
set = my_set.h my_set.cpp
int = big_integer.h big_integer.cpp

setbuild: $(int) $(set) 
	$(CXX) $(CXXFLAGS) -o testset $(set) $(int) my_set_tester.cpp

intbuild: $(int) 
	$(CXX) $(CXXFLAGS) -o testint $(int) big_int_tester.cpp

all: intbuild setbuild

testint: intbuild
	./testint

testset: setbuild 
	./testset

clean:
	rm -f *.o testint testset
