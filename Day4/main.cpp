#include <stdio.h>
#include <sstream>
#include <algorithm>
#include "FileInput.hpp"
#include <regex>

class passport {
	int byr;
	int iyr;
	int eyr;
	std::string hgt;
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
                std::regex re("1[5-8][0-9]cm|19[0-3]cm|[5-6][0-9]in|[7][0-6]in");
                if (!std::regex_match(hgt.c_str(), m, re)) {
                    hgt = "";
                } 
            } else if (key == "hcl") {
                sss >> hcl;
                std::regex re("#[0-9a-fA-F]{6}");
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
        hgt = "";
        hcl = "";
        ecl = "";
        pid = "";
        cid = -1;
    }

    bool isValid() const
    {
        //std::cout << byr << "\t\t" <<  iyr << "\t\t" <<  eyr << "\t\t" <<  hgt << "\t\t" <<  hcl << "\t\t" <<  ecl << "\t\t" <<  pid << "\t\t" <<  cid << std::endl;
        return (byr != -1) && (iyr != -1) && (eyr != -1) && (hgt != "") && (hcl != "") && (ecl != "") && (pid != ""); 
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
	FileInput input("Day4/input.txt");
	std::string line;
    passport pas;
	long num = 0;

	std::vector<passport> list;

	while (input.getNext(line)) {  // TODO: update

        if (line.size() == 0) {
            if (pas)
                num++;
            list.push_back(pas);
            pas.clear();
        }
        pas.update(line);
	}

    if (pas)
        num++;

    std::cout << num << std::endl;
	return 0;
}