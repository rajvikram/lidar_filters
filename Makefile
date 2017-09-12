

BOOST_CFLAGS = -I /opt/local/include

all: lidar matrixOp

clean:
	rm -f *.o lidar matrixOp

filterTest:
    g++ $(BOOST_CFLAGS) filterTest.cpp

lidar: Lidar.cpp
	g++ Lidar.cpp -o lidar

matrixOp: MatrixOp.cpp
	g++ Matrix.cpp -o matrixOp

