

all: filterTest

clean:
	rm -f *.o filterTest

test: filterTest.cpp rangeFilter.hpp temporalFilter.hpp
	g++ filterTest.cpp -o filterTest
	./filterTest

docs: FORCE
	doxygen doxygen.cfg

FORCE: