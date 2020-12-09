#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

bool checkValid(std::vector<int>::iterator back, std::vector<int>::iterator front, int num) 
{
    for (auto i=back; i!=front; i++)
        for (auto j=i+1; j!=front+1; j++)
            if ((*i) + (*j) == num)
                return true;

    return false;
}

int main()
{
    std::ifstream file("Day9/input.txt");
    std::string line;
    int num;

    std::vector<int> numbers;

    if (!file.is_open()) {
        return -1;
    }
 
    while (file >> num)
        numbers.push_back(num);

    auto back = numbers.begin();
    auto front = numbers.begin() + 25;

    while (front != numbers.end()-2) {
        if (!checkValid(back, front, *(front+1))) {
            std::cout << "First invalid: " << *(front+1) << std::endl;
            return 0;
        }
        front++;
        back++;
    }

    std::cout << "No invalid" << std::endl;
    return -1;
}