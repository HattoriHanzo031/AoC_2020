#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Bus {
    int id;
    int timeDifference;
};

int main()
{
    std::string line;
    std::ifstream file("Day13/input.txt");
    std::vector<Bus> busses;

    if (!file.is_open())
        return -1;

    getline(file, line);

    int difference = 0;
    while (getline(file, line, ',')) {
        if (line != "x")
            busses.push_back({stoi(line), difference});
        difference++;
    }

    long long timestamp = 0; // current timestamp to test
    long long repeatPeriod = busses[0].id; // number of timestamps after which the current cycle would repeat
    auto bus = busses.begin()+1; // current bus line to check for alingment

    /*
     * We first find when the bus 0 and bus 1 align (with required time difference) by checking at 
     * each timestamp the bus 0 arives. The same alingment will ocurr after bus0 ID * bus1 ID timestamps
     * so we check only after that period for the next bus. Do the same for all remaining busses.
     */
    while (true) {
        timestamp += repeatPeriod;
        if((timestamp + bus->timeDifference) % bus->id == 0) {
            repeatPeriod *= bus->id;
            if (++bus == busses.end())
                break;
        }
    }
    
    std::cout << "Timestamp: " << timestamp << std::endl;

    return 0;
}