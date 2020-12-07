#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <map>
#include <sstream>

struct bagRule {
    bagRule(int _num, std::string _id) : num(_num), id(_id) {}
    int num;
    std::string id;
};

void calculatePart1(
        std::map<std::string, std::vector<std::string>>& containedIn, 
        std::unordered_set<std::string>& bagsContainingMine, 
        std::string& currentId)
{
    auto parrents = containedIn[currentId];
    for (auto parrent : parrents) {
        bagsContainingMine.insert(parrent);
        calculatePart1(containedIn, bagsContainingMine, parrent);
    }
}

int calculatePart2(std::map<std::string, std::vector<bagRule>>& contains, std::string& currentId)
{
    int sum = 1; // 1 to include the current bag also
    auto parrents = contains[currentId];
    for (auto parrent : parrents) {
        sum += parrent.num * calculatePart2(contains, parrent.id);
    }
    return sum;
}

int main()
{
    std::ifstream file("Day7/input.txt");
	std::string line;
    std::string texture;
    std::string color;
    std::map<std::string, std::vector<std::string>> containedIn;
    std::map<std::string, std::vector<bagRule>> contains;

	while (getline(file, line)) {
        std::string token;
        std::stringstream ss(line);

        ss >> texture;
        ss >> color;
        std::string parrent(texture.append(color));

        ss >> token >> token; // ignore "bag(s) contain"
        
        while (true) {
            ss >> token; // number of bags
            if (token == "no")
                break;

            int num = std::stoi(token);
            ss >> texture;
            ss >> color;
            std::string bagId(texture.append(color));

            containedIn[bagId].push_back(parrent);
            contains[parrent].push_back(bagRule(num, bagId));

            ss >> token; // "bag(s),."s"
            if (token.back() == '.')
                break;
        }
	}

    std::string myBag("shinygold");

    std::unordered_set<std::string> bagsContainingMine;
    calculatePart1(containedIn, bagsContainingMine, myBag);
    std::cout << "Kofera u koji ide moj kofer: " << bagsContainingMine.size() << std::endl;

    int sum = calculatePart2(contains, myBag) - 1; // -1 to exclude mmy bag
    std::cout << "Ukupno kofera u mom koferu: " << sum << std::endl;

    return 0;
}