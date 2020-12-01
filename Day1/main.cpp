#include <stdio.h>
#include "FileInput.hpp"

int main (int argc, char* argv[])
{
	(void) argc;
	(void) argv;
	FileInput input("Day1/input.txt");
	std::vector<int> in; 
	input.getInput(in);

	for (auto i = in.begin(); i != in.end(); i++) {
		for (auto j = i+1; j != in.end(); j++) {
			if (*i + *j >= 2020) continue; // Optimization
			for (auto k = j+1; k != in.end(); k++) {
				if (*i + *j + *k == 2020) {
					std::cout << "Resenje je: " << *i << " * " << *j << " * " << *k << " = " << *i * *j * *k << std::endl;
					return 0;
				}
			}
		}
	}
	return -1;
}
