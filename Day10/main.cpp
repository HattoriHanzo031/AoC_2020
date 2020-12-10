#include <iostream>
#include <fstream>
#include <set>

int main()
{
    std::ifstream file("Day10/input.txt");
    int num, prev = 0;
    int counter[3] = {0};
    std::set<int> jolts;

    if (!file.is_open())
        return -1;

    while (file >> num)
        jolts.insert(num);

    for (auto jolt : jolts) {
        counter[jolt-prev-1]++;
        prev = jolt;
    }
    counter[2]++; // to the device

    std::cout << "Number of 1-jolt differences: " << counter[0] << " Number of 3-jolt differences:" << counter[2] \
              << " Solution: " << counter[0] * counter[2] << std::endl;
    return 0;
}