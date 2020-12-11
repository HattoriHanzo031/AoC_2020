#include <iostream>
#include <fstream>
#include <map>
#include <vector>

struct Direction
{
    Direction(int xIncrement, int yIncrement, int rows, int columns) :
        xIncrement(xIncrement),
        yIncrement(yIncrement),
        xLimit(-1),
        yLimit(-1)
    {
        // Set limits depending on the dirrection
        if (xIncrement == 1)
            xLimit = rows-1;
        else if (xIncrement == -1)
            xLimit = 0;

        if (yIncrement == 1)
            yLimit = columns-1;
        else if (yIncrement == -1)
            yLimit = 0;
    }

    // Move one step in this direction. Returns false if the edge is reached
    bool goDirection(std::pair<int, int>& coordinate)
    {
        if(coordinate.first == xLimit || coordinate.second == yLimit)
            return false;

        coordinate.first += xIncrement;
        coordinate.second += yIncrement;
        return true;
    }

    int xIncrement;
    int yIncrement;
    int xLimit;
    int yLimit;
};

// Check adjacent seats and return new value for the seat
char updateSeat(std::map<std::pair<int,int>, char>& seats, std::pair<int,int> coordinates, bool& updated, int rows, int columns)
{
    std::vector<Direction> directions = { //8 possible directions
        Direction(-1, -1, rows, columns),
        Direction(-1,  0, rows, columns),
        Direction(-1,  1, rows, columns),
        Direction( 0, -1, rows, columns),
        Direction( 0,  1, rows, columns),
        Direction( 1, -1, rows, columns),
        Direction( 1,  0, rows, columns),
        Direction( 1,  1, rows, columns),
    };

    int countHash = 0;

    // ======== Optimisation ====== //
    int breakAt = 1;
    if (seats[coordinates] == '#')
        breakAt = 5;
    // ====== End optimisation ==== //

    for (auto dir: directions) { // try all 8 directions
        auto coord(coordinates);
        while (dir.goDirection(coord)) { // go one step in selected direction and update new coordinates
            auto seat = seats.find(coord); // get the seat at new coordinates
            if (seat == seats.end()) // if there is no seat go one step further
                continue;

            if(seat->second == '#') // if seat is ocupied, count it
                countHash++;

            break;
        }

        // ======== Optimisation ====== //
        if (countHash >= breakAt)
            break;
        // ====== End optimisation ==== //
    }

    // Check if seat needs to be updated and return new value
    updated = true;
    if (seats[coordinates] == 'L' && countHash == 0) {
        return '#';
    } else if(seats[coordinates] == '#' && countHash >= 5) {
        return 'L'; 
    }

    updated = false;
    return seats[coordinates];
}

// Print map (for debugging)
void printSeats(std::map<std::pair<int,int>, char>& seats, int rows, int columns)
{
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<columns; j++) {
            auto seat = seats.find(std::make_pair(i, j));
            if (seat == seats.end())
                std::cout << '.';
            else 
                std::cout << seat->second;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    std::string line;
    std::map<std::pair<int,int>, char> seats;
    std::ifstream file("Day11/input.txt");

    if (!file.is_open())
        return -1;

    int row = 0;
    int column = 0;
    while (file >> line) {
        column = 0;
        for (auto c : line) {
            if (c == 'L') // insert only the seats and not the blank places
                seats.insert(std::make_pair(std::make_pair(row, column), c));

            column++;
        }
        row++;
    }
    //printSeats(seats, row, column);

    std::map<std::pair<int,int>, char> seatsCopy;
    bool somethingChanged;
    do {
        somethingChanged = false;
        // go trough all of the seats
        for (auto it = seats.begin(); it != seats.end(); it++) {
            bool updated;
            // need to use copy of the map so that updated values don't affect further calculations
            seatsCopy[it->first] = updateSeat(seats, it->first, updated, row, column);

            somethingChanged = somethingChanged || updated;
        }

        seats = seatsCopy; // very inefficient TODO: try to switch between two maps instead of copying
        //printSeats(seats, row, column);
    } while (somethingChanged);

    int count = 0;
    for (auto seat : seats) {
        if (seat.second == '#')
            count++;
    }

    std::cout << "Occupied seats at the end: " << count << std::endl;

    return 0;
}