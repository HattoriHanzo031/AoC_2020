#include <stdio.h>
#include <sstream>
#include <algorithm>
#include "FileInput.hpp"

struct passport {
	int byr;
	int iyr;
	int eyr;
	int hgt;
	std::string hcl;
	std::string ecl;
	int pid;
	int cid;

    passport()
    {
        clear();
    }

    void update(std::string line)
    {
        std::stringstream ss(line);
        std::string key;
        std::string token;
        while (ss.peek() != EOF) {
            ss >> token;
            std::stringstream sss(token);
            std::getline(sss, key, ':');
            if (key == "byr") {
                sss >> byr;
            } else if (key == "iyr") {
                sss >> iyr;
            } else if (key == "eyr") {
                sss >> eyr;
            } else if (key == "hgt") {
                sss >> hgt;
            } else if (key == "hcl") {
                sss >> hcl ;
            } else if (key == "ecl") {
                sss >> ecl;
            } else if (key == "pid") {
                sss >> pid;
            } else if (key == "cid") {
                sss >> cid;
            }
        }
    }

    void clear() 
    {
        byr = -1;
        iyr = -1;
        eyr = -1;
        hgt = -1;
        hcl = "";
        ecl = "";
        pid = -1;
        cid = -1;
    }
    bool isValid()
    {
        return (byr != -1) && (iyr != -1) && (eyr != -1) && (hgt != -1) && (hcl != "") && (ecl != "") && (pid != -1); 
    }
};

int main (int argc, char* argv[])
{
	(void) argc;
	(void) argv;
	FileInput input("Day4/input.txt");
	std::string line;
    passport pas;
	long num = 0;

	std::vector<passport> list;

	while (input.getNext(line)) {
        if (line.size() == 0) {
            if (pas.isValid())  // TODO: update
                num++;
            list.push_back(pas);
            pas.clear();
        }
        pas.update(line);
	}
    if (pas.isValid())
        num++;
    std::cout << num << std::endl;
	return 0;
}