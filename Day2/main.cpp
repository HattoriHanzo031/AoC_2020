#include <stdio.h>
#include <sstream>
#include <algorithm>
#include "FileInput.hpp"

struct passRule {
	int min;
	int max;
	char c;
	std::string pass;

	passRule(std::string line)
	{
		std::stringstream ss(line);
		ss >> min;
		ss.ignore(1);
		ss >> max;
		ss >> std::skipws >> c;
		ss.ignore(1);
		ss >> std::skipws >> pass;
	}

	bool inline isValid() const
	{
		int count = std::count(pass.begin(), pass.end(), c);
		return (count <= max) && (count >= min);
	}

	operator bool() const
	{
		return this->isValid();
	}
};

int main (int argc, char* argv[])
{
	(void) argc;
	(void) argv;
	int num_valid = 0;
	FileInput input("Day2/input.txt");
	std::string line;

	while (input.getNext(line)) {
		if (passRule(line)) {
			num_valid++;
		}
	}

	std::cout << "Ispravnih: " << num_valid << std::endl;

	return 0;
}