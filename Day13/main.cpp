#include <iostream>
#include <fstream>
#include <vector>

struct Bus {
    unsigned id;
    unsigned timeDifference;
};

int main()
{
    std::string line;
    std::ifstream file("Day13/input.txt");
    std::vector<Bus> busses;

    if (!file.is_open())
        return -1;

    getline(file, line);

    unsigned difference = 0;
    while (getline(file, line, ',')) {
        if (line != "x")
            busses.push_back({stoi(line), difference});
        difference++;
    }

    for (auto bus : busses) {
        std::cout << bus.id << " " << bus.timeDifference << std::endl;
    }

    unsigned long long targetTime = 0;
    bool foundSolution = false;

    unsigned long long prev = 29;

    while (!foundSolution) {
        targetTime += busses[0].id;
        //std::cout << targetTime;
        foundSolution = true;
        for (auto bus = busses.begin()+1; bus != busses.end(); bus++) {
            //std::cout << " ID:" << bus->id << " TD:" << bus->timeDifference << " - " << (targetTime % bus->id) << " "; 
            if(bus->id - (targetTime % bus->id) != bus->timeDifference) {
                foundSolution = false;
                break;
            }
        }
        //std::cout << std::endl;
    }
    
    std::cout << "Timestamp: " << targetTime << std::endl;

    return 0;
}