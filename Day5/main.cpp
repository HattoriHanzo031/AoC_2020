#include <string>
#include <iostream>
#include <fstream>

int main (int argc, char* argv[])
{
	(void) argc;
	(void) argv;
    std::ifstream file("Day5/input.txt");
	long max = 0;
    std::string line;

	while (getline(file, line)) {
        int id = 0;
        for (int i=0; i<10; i++) {
            id <<= 1;
            if (line.at(i) == 'B' || line.at(i) == 'R')
                id |= 1;
        }

        if (id > max)
            max = id;
	}

    std::cout << max << std::endl;
	return 0;
}