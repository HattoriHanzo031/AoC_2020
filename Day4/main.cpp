#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <regex>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class passport {
	int byr;
	int iyr;
	int eyr;
	int hgt;
	std::string hcl;
	std::string ecl;
	std::string pid;
	int cid;

public:
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
            std::cmatch m;
            ss >> token;
            std::stringstream sss(token);
            std::getline(sss, key, ':');
            if (key == "byr") {
                sss >> byr;
                if(byr<1920 || byr>2002)
                    byr = -1;
            } else if (key == "iyr") {
                sss >> iyr;
                if(iyr<2010 || iyr>2020)
                    iyr = -1;
            } else if (key == "eyr") {
                sss >> eyr;
                if(eyr<2020 || eyr>2030)
                    eyr = -1;
            } else if (key == "hgt") {
                sss >> hgt;
                std::string unit;
                sss >> unit;
                if (unit == "cm") {
                    if ((hgt<150) || (hgt>193)) {
                        hgt = -1;
                    }
                } else if (unit == "in") {
                    if ((hgt<59) || (hgt>76)) {
                        hgt = -1;
                    }
                } else {
                    hgt = -1;
                }
                /*std::regex re("1[5-8][0-9]cm|19[0-3]cm|[5-6][0-9]in|[7][0-6]in");
                if (!std::regex_match(hgt.c_str(), m, re)) {
                    hgt = "";
                }*/
            } else if (key == "hcl") {
                sss >> hcl;
                std::regex re("#[0-9a-f]{6}");
                if (!std::regex_match(hcl.c_str(), m, re)) {
                    hcl = "";
                }
            } else if (key == "ecl") {
                sss >> ecl;
                std::regex re("amb|blu|brn|gry|grn|hzl|oth");
                if (!std::regex_match(ecl.c_str(), m, re)) {
                    ecl = "";
                }
            } else if (key == "pid") {
                sss >> pid;
                std::regex re("[0-9]{9}");
                if (!std::regex_match(pid.c_str(), m, re)) {
                    pid = "";
                }
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
        pid = "";
        cid = -1;
    }

    bool isValid() const
    {
        //std::cout << byr << "\t\t" <<  iyr << "\t\t" <<  eyr << "\t\t" <<  hgt << "\t\t" <<  hcl << "\t\t" <<  ecl << "\t\t" <<  pid << "\t\t" <<  cid << std::endl;
        return (byr != -1) && (iyr != -1) && (eyr != -1) && (hgt != -1) && (hcl != "") && (ecl != "") && (pid != "");
    }

	operator bool() const
	{
		return isValid();
	}
};

int main (int argc, char* argv[])
{
	(void) argc;
	(void) argv;
    std::ifstream file("Day4/input.txt");
	std::string line;
    passport pas;
	long num = 0;

	while (getline(file, line)) {
        if (line.size() == 0 || file.peek() == EOF) {
            if (pas)
                num++;
            pas.clear();
        }
        pas.update(line);
	}

    std::cout << num << std::endl;
	return 0;
}