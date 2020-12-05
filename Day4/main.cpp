#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <regex>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

bool chekPassport(std::vector<std::string>& niz)
{
    for (auto token : niz) {
        std::string key;
        int intValue;
        std::string value;
        std::cmatch m;

        if (niz.size() < 7)
            return false;

        std::stringstream ss(token);
        std::getline(ss, key, ':');
        ss >> value;
        if (key == "byr") {
            intValue = stoi(value);
            if(intValue<1920 || intValue>2002)
                return false;
        } else if (key == "iyr") {
            intValue = stoi(value);
            if(intValue<2010 || intValue>2020)
                return false;
        } else if (key == "eyr") {
            intValue = stoi(value);
            if(intValue<2020 || intValue>2030)
                return false;
        } else if (key == "hgt") {
            std::stringstream sss(value);
            std::string unit;
            sss >> intValue;
            sss >> unit;
            if (unit == "cm") {
                if ((intValue<150) || (intValue>193)) {
                    return false;
                }
            } else if (unit == "in") {
                if ((intValue<59) || (intValue>76)) {
                    return false;
                }
            } else {
                return false;
            }
            /*std::regex re("1[5-8][0-9]cm|19[0-3]cm|[5-6][0-9]in|[7][0-6]in");
            if (!std::regex_match(hgt.c_str(), m, re)) {
                hgt = "";
            }*/
        } else if (key == "hcl") {
            std::regex re("#[0-9a-f]{6}");
            if (!std::regex_match(value.c_str(), m, re)) {
                return false;
            }
        } else if (key == "ecl") {
            std::regex re("amb|blu|brn|gry|grn|hzl|oth");
            if (!std::regex_match(value.c_str(), m, re)) {
                return false;
            }
        } else if (key == "pid") {
            std::regex re("[0-9]{9}");
            if (!std::regex_match(value.c_str(), m, re)) {
                return false;
            }
        } else if (key == "cid") {
            if (niz.size() == 7)
                return false;
        } else {
            return false;
        }
    }
    return true;
}

int main (int argc, char* argv[])
{
	(void) argc;
	(void) argv;
    std::ifstream file("Day4/input.txt");
	std::string line;
	long num = 0;
    std::vector<std::string> niz;

	while (getline(file, line)) {
        if (line.size() == 0 || file.peek() == EOF) {
            if (chekPassport(niz))
                num++;

            niz.clear();
        }
        std::string segment;
        std::stringstream ss(line);
        while (ss >> segment) {
            niz.push_back(segment);
        }
	}

    std::cout << num << std::endl;
	return 0;
}