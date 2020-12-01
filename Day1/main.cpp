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
			if (*i + *j == 2020) {
				std::cout << "Resenje je: " << *i << " * " << *j << " = " << *i * *j << std::endl;
			}
		}
	}
	return 0;
}
