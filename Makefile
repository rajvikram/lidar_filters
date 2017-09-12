

all: filterTest

clean:
	rm -f *.o filterTest

test: filterTest.cpp
	g++ -ggdb filterTest.cpp -o filterTest
	./filterTest



