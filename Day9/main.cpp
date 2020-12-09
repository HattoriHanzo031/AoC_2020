#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

bool checkValid(std::vector<long>::iterator start, std::vector<long>::iterator end, long num) 
{
    for (auto i=start; i!=end; i++)
        for (auto j=i+1; j!=end+1; j++)
            if ((*i) + (*j) == num)
                return true;

    return false;
}

int main()
{
    std::ifstream file("Day9/input.txt");
    std::string line;
    long num;
    long invalidNum = 0;
    std::vector<long> numbers;

    if (!file.is_open()) {
        return -1;
    }
 
    while (file >> num)
        numbers.push_back(num);

    auto start = numbers.begin();       // start of the range
    auto end = numbers.begin() + 25;    // end of the range

    // go trough all the numbers
    while (end != numbers.end()-2) {
        invalidNum = *(end+1);
        if (!checkValid(start, end, invalidNum)) {
            std::cout << "First invalid: " << invalidNum << std::endl;
            break;
        }
        // move the search window by one to the right
        start++;
        end++;
    }

    for (start = numbers.begin(); start!=numbers.end()-2; start++) {
        end = start+1;
        long sum = (*start) + (*end); // sum first two numbers

        // sum following numbers until sum is greater or equal to invalid number
        while (sum < invalidNum) {
            end++; 
            sum += *end;
        }
        // Did we find correct contiguous set of numbers
        if (sum == invalidNum) {
            long min = *std::min_element(start, end+1);
            long max = *std::max_element(start, end+1);
            std::cout << "Min: " << min << " Max: " << max << " Min+Max: " << min + max << std::endl;

            return 0;
        }
    }

    std::cout << "No invalid" << std::endl;
    return -1;
}