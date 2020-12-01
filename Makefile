SHELL := /bin/bash
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -Og -g -I ./common
DEPS = $(wildcard ./common/*.cpp)

day% : Day%/main.o $(DEPS)
	@$(CXX) $(CPPFLAGS) $^ -o $@

clean:
	@rm -f day? day??

time%: day%
	time for i in {1..100}; do ./$<; done
