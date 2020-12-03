#include <stdio.h>
#include <sstream>
#include <algorithm>
#include "FileInput.hpp"

int num_trees(std::vector<std::pair<int, int>>& map, int rows, int columns, std::pair<int, int> slope) {
	int num = 0;
	for (int i = 0; i<rows; i++) {
		if (std::find(map.begin(), map.end(), std::pair<int,int>((i*slope.first) % columns, i*slope.second)) != map.end()) {
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
	int x = 0;
	int y = 0;
	long num = 1;

	std::vector<std::pair<int, int>> map;

	while (input.getNext(line)) {
		x=-1;
		while (true) {
			x = line.find('#', x+1);
			if(x == (int)std::string::npos)
				break;
			map.push_back(std::pair<int,int>(x,y));
		}
		y++;
	}

	std::vector<std::pair<int, int>> slopes = {{1,1}, {3,1}, {5,1}, {7,1}, {1,2}};

	for(auto i=slopes.begin(); i!=slopes.end(); i++) {
		num *= num_trees(map, y, line.size(), *i);
	}

	std::cout << "Resenje je: " << num << std::endl;

	return 0;
}