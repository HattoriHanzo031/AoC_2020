SHELL := /bin/bash
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -Og -g -I ./common
DEPS = $(wildcard ./common/*.cpp)

d% : Day%/main.o $(DEPS)
	@$(CXX) $(CPPFLAGS) $^ -o $@

clean:
	@rm -f d? d??

time%: d%
	time for i in {1..100}; do ./$<; done
