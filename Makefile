main: matrix.cpp
	g++ -std=c++11 matrix.cpp -o main

clean:
	rm -f *.o main

