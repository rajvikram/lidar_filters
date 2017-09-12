

all: test 

clean:
	rm -f *.o filterTest

test: filterTest.cpp rangeFilter.hpp temporalFilter.hpp
	g++ -std=c++11 filterTest.cpp -lpthread -o filterTest
	./filterTest

docs: FORCE
	doxygen doxygen.cfg

FORCE:
