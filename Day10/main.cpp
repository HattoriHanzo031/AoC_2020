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

    prev = adapters.rbegin()->jolts + 3; // Device jolts (Part 1)
    adapters.rbegin()->arrangements = 1; // Only one possible arrangement for the adapter with highest jolts
    
    /*
     * Start from the top and calculate possible arrangements for each adapter by summing up
     * possible arrangements of all adapters that can be combined with it
     */
    for (auto adapter = adapters.rbegin(); adapter != adapters.rend(); adapter++) {
        // Part 1 code
        // calculate the difference between two adjacent adapters and increment the counter array at that index
        int diff = prev - adapter->jolts;
        counter[diff-1]++;
        prev = adapter->jolts;
        // End of Part 1 code

        /*
         * go back maximum of 3 adapters (only ones that can be combined with current adapter)
         * and sum all their possible arrangements to get the number of possible arrangements
         * of the current one
         */
        auto compare = adapter-1;
        while(compare != adapters.rbegin()-1 && (compare->jolts - adapter->jolts) <= 3) {
            adapter->arrangements += compare->arrangements;
            compare--;
        }
    }
 
    std::cout << "Number of 1-jolt differences: " << counter[0] << " Number of 3-jolt differences:" << counter[2] \
              << "\nPart 1 solution: " << counter[0] * counter[2] << std::endl;
    std::cout << "Arrangements: " << adapters.begin()->arrangements << std::endl;

    return 0;
}