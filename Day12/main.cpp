#include <iostream>
#include <fstream>
#include <sstream>

struct coordinate {
    int x;
    int y;
};

int main()
{
    std::string line;
    char c;
    int num;
    int tmp;
    coordinate ship = {0, 0};
    coordinate waypoint = {10, 1};

    std::ifstream file("Day12/input.txt");

    if (!file.is_open())
        return -1;

    while (getline(file, line)) {
        std::stringstream ss(line);
        ss >> c;
        ss >> num;
        switch (c)
        {
        case 'N':
            waypoint.y += num;
            break;
        case 'S':
            waypoint.y -= num;
            break;
        case 'E' :
            waypoint.x += num;
            break;
        case 'W' :
            waypoint.x -= num;
            break;
        case 'R' :
            for (int i=0; i<num; i+=90) {
                tmp = waypoint.y;
                waypoint.y = - waypoint.x;
                waypoint.x = tmp;
            }
            break;
        case 'L' :
            for (int i=0; i<num; i+=90) {
                tmp = waypoint.y;
                waypoint.y = waypoint.x;
                waypoint.x = -tmp;
            }
            break;
        case 'F' :
            ship.x += num*waypoint.x;
            ship.y += num*waypoint.y;
        default:
            break;
        }
    }

    std::cout << "x: " << ship.x << " y: " << ship.y << " Manhattan distance: " << std::abs(ship.x) + std::abs(ship.y) << std::endl;
    return 0;
}