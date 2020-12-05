#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main (int argc, char* argv[])
{
	(void) argc;
	(void) argv;
    std::ifstream file("Day5/input.txt");
    std::string line;
    std::vector<int> list;
    int seat;

	while (getline(file, line)) {
        int id = 0;
        for (int i=0; i<10; i++) {
            id <<= 1;
            if (line.at(i) == 'B' || line.at(i) == 'R')
                id |= 1;
        }
        list.push_back(id);
	}

    std::sort(list.begin(), list.end());
    std::cout << "Max: " << list.back() << std::endl;

    seat = list[0];
    for (auto item : list) {
        if (item != seat)
            break;
        seat++;
    }

    std::cout << "Seat ID: " << seat-1 << std::endl;
    return 0;
}