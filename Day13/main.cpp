#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::string line;
    std::ifstream file("Day13/input.txt");
    std::vector<int> timestamps;

    if (!file.is_open())
        return -1;

    getline(file, line);
    int earliest = std::stoi(line);
    
    while (getline(file, line, ',')) {
        if (line != "x")
            timestamps.push_back(stoi(line));
    }

    int id = 0;
    int closest = earliest;
    for (auto t : timestamps) {
        // unlikely it will happen but just in case check if the bus arrives exacly at our earliest time 
        if(earliest % t == 0) {
            closest = 0;
            break;
        }

        int timeToWait = (t - (earliest % t));
        if (timeToWait < closest) {
            closest = timeToWait;
            id = t;
        }
    }
    std::cout << "ID: " << id << "\tTime to wait: " << closest << "\tSolution: " << id*closest << std::endl;

    return 0;
}