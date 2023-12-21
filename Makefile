CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: main

main: main.cpp NearestNeighbor.o
	$(CXX) $(CXXFLAGS) $^ -o $@

NearestNeighbor.o: NearestNeighbor.cpp NearestNeighbor.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f main *.o

rebuild: clean all
