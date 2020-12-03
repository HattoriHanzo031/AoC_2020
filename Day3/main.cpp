#include <stdio.h>
#include <sstream>
#include <algorithm>
#include "FileInput.hpp"

int num_trees(std::vector<std::pair<int, int>>& map, int rows, int columns, int slope) {
	std::cout << rows << " " << columns << std::endl;
	int num = 0;
	for (int i = 0; i<rows; i++) {
		if (std::find(map.begin(), map.end(), std::pair<int,int>((i*slope) % columns, i)) != map.end()) {
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
	int num;

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

	num = num_trees(map, y, line.size(), 3);

	std::cout << "Resenje je: " << num << std::endl;

	return 0;
}

