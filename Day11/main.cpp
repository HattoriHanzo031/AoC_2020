#include <iostream>
#include <fstream>
#include <map>

char updateSeat(std::map<std::pair<int,int>, char>& seats, std::pair<int,int> coordinates, bool& updated)
{
    int countHash = 0;
    for (int x=-1; x<=1; x++) {
        for (int y =-1; y<=1; y++) {
            if (x == 0 && y == 0)
                continue;

            auto seat = seats.find(std::make_pair(coordinates.first+x, coordinates.second+y));
            if (seat != seats.end() && seat->second == '#')
                countHash++;
            else
                continue;
        }
    }

    updated = true;
    if (seats[coordinates] == 'L' && countHash == 0) {
        return '#';
    } else if(seats[coordinates] == '#' && countHash >= 4) {
        return 'L'; 
    }

    updated = false;
    return seats[coordinates];
}

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
            if (c == 'L')
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
        for (auto it = seats.begin(); it != seats.end(); it++) {
            bool updated;
            seatsCopy[it->first] = updateSeat(seats, it->first, updated);

            somethingChanged = somethingChanged || updated;
        }
        seats = seatsCopy;
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