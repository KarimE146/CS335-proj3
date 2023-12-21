CXX = g++
CXXFLAGS = -std=c++11 -Wall

HDRS = NearestNeighbor.hpp

SRCS = $(wildcard *.cpp)

OBJS = $(SRCS:.cpp=.o)

EXEC = main

.PHONY: all clean rebuild

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

# Rule to build object files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

rebuild: clean all
