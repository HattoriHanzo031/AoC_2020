#include <stdio.h>
#include <sstream>
#include <algorithm>
#include "FileInput.hpp"

int num_trees(std::vector<std::string>& map, std::pair<int, int> slope) {
	int num = 0;
	int columns = map[0].size();

	for (unsigned i = 0; i < map.size()/slope.second; i++) {
		if (map[i*slope.second].at((i*slope.first) % columns) == '#') {
			num++;
		}
	}
	return num;
}

int main (int argc, char* argv[])
{
	(void) argc;
	(void) argv;
	FileInput input("Day3/input.txt");
	std::string line;

	long num = 1;

	std::vector<std::string> map;

	while (input.getNext(line)) {
		map.push_back(line);
	}

	std::vector<std::pair<int, int>> slopes = {{1,1}, {3,1}, {5,1}, {7,1}, {1,2}};

	for(auto i=slopes.begin(); i!=slopes.end(); i++) {
		num *= num_trees(map, *i);
	}

	std::cout << "Resenje je: " << num << std::endl;

	return 0;
}