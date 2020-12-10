#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Adapter {
    int jolts;
    long long arrangements;
    friend bool operator<(const Adapter& l, const Adapter& r)
    {
        return l.jolts < r.jolts;
    }
};

int main()
{
    std::ifstream file("Day10/input.txt");
    int num, prev;
    int counter[3] = {0};
    std::vector<Adapter> adapters;

    if (!file.is_open())
        return -1;

    adapters.push_back({0, 0}); //outlet jolts

    while (file >> num)
        adapters.push_back({num, 0});

    std::sort(adapters.begin(), adapters.end());

    prev = adapters.rbegin()->jolts + 3; // Device jolts
    adapters.rbegin()->arrangements = 1; // Only one path to the device from the biggest element
    
    for (auto adapter = adapters.rbegin(); adapter != adapters.rend(); adapter++) {
        int diff = prev - adapter->jolts;
        counter[diff-1]++;
        prev = adapter->jolts;

        auto compare = adapter-1;
        while(compare != adapters.rbegin()-1 && (compare->jolts - adapter->jolts) <= 3) {
            adapter->arrangements += compare->arrangements;
            compare--;
        }
    }
 
    std::cout << "Number of 1-jolt differences: " << counter[0] << " Number of 3-jolt differences:" << counter[2] \
              << "\nPart1 solution: " << counter[0] * counter[2] << std::endl;
    std::cout << "Arrangements " << adapters.begin()->arrangements << std::endl;

    return 0;
}