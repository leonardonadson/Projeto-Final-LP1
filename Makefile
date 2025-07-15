CXX      := g++
CXXFLAGS := -Iinclude -std=c++17 -Wall
SRCS_CPP := $(wildcard src/*.cpp)

.PHONY: all clean run

all: final_cpp

final_cpp:
	$(CXX) $(CXXFLAGS) $(SRCS_CPP) -o final_cpp

run: final_cpp
	./final_cpp

clean:
	rm -f final_cpp