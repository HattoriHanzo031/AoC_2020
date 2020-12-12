#include <iostream>
#include <fstream>
#include <sstream>

enum Direction {
    N = 0,
    S = 1,
    E = 2, 
    W = 3,
};

struct coordinate {
    int x;
    int y;
};

int main()
{
    std::string line;
    char c;
    int num;
    coordinate ship = {0, 0};

    const coordinate dir[4] = {
        { 0,  1}, // N
        { 0, -1}, // S
        { 1,  0}, // E
        {-1,  0}  // W
    };

    std::ifstream file("Day12/input.txt");

    if (!file.is_open())
        return -1;

    enum Direction movingDir = E;
    enum Direction shipDir = E;

    while (getline(file, line)) {
        std::stringstream ss(line);
        ss >> c;
        ss >> num;
        switch (c)
        {
        case 'N':
            movingDir = N;
            break;
        case 'S':
            movingDir = S;
            break;
        case 'E' :
            movingDir = E;
            break;
        case 'W' :
            movingDir = W;
            break;
        case 'L' :
            shipDir = (enum Direction)((shipDir + (num/90)) % 4);
            movingDir = shipDir;
            num = 0;
            break;
        case 'R' :
            shipDir = (enum Direction)((4 + shipDir - (num/90)) % 4);
            movingDir = shipDir;
            num = 0;
            break;
        case 'F' :
            movingDir = shipDir;
        default:
            break;
        }


        ship.x += num * (dir[movingDir].x);
        ship.y += num * (dir[movingDir].y);
        //std::cout << num << " " << dir[movingDir].x << " " << dir[movingDir].y << " - x:" << x << " y:" << y << std::endl;
    }

    std::cout << "x: " << ship.x << " y: " << ship.y << " Manhattan distance: " << std::abs(ship.x) + std::abs(ship.y) << std::endl;
    return 0;
}