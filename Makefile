CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -Og -g -I ./common
DEPS = $(wildcard ./common/*.cpp)

day% : Day%/main.o $(DEPS)
	@$(CXX) $(CPPFLAGS) $^ -o $@

clean:
	@rm -f day? day??