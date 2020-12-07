#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <map>
#include <sstream>

struct bagRule {
    bagRule(int _num, uint16_t _id) : num(_num), id(_id) {}
    int num;
    uint16_t id;
};

uint8_t textureToId(std::string& texture) {
    static uint8_t ID = 0;
    static std::map<std::string, uint8_t> textures;

    auto it = textures.find(texture);
    if (it != textures.end())
        return it->second;

    textures.insert(std::make_pair(texture, ID));
    return ID++;
}

uint8_t colorToId(std::string& color) {
    static uint8_t ID = 0;
    static std::map<std::string, uint8_t> colors;

    auto it = colors.find(color);
    if (it != colors.end())
        return it->second;

    colors.insert(std::make_pair(color, ID));
    return ID++;
}

uint16_t stringToId(std::string& texture, std::string& color)
{
    return (textureToId(texture) << 8) + colorToId(color);
}

void calculatePart1(std::map<uint16_t, std::vector<uint16_t>>& containedIn, std::unordered_set<uint16_t>& out, uint16_t currentId)
{
    auto parrents = containedIn[currentId];
    for (auto parrent : parrents) {
        out.insert(parrent);
        calculatePart1(containedIn, out, parrent);
    }
}


int calculatePart2(std::map<uint16_t, std::vector<bagRule>>& contains, uint16_t currentId)
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
    std::map<uint16_t, std::vector<uint16_t>> containedIn;
    std::map<uint16_t, std::vector<bagRule>> contains;

	while (getline(file, line)) {
        std::string token;
        std::stringstream ss(line);

        ss >> texture;
        ss >> color;
        uint16_t parrent = stringToId(texture, color);

        ss >> token >> token; // ignore "bag(s) contain"
        
        while (true) {
            ss >> token; // number of bags
            if (token == "no")
                break;

            int num = std::stoi(token);
            ss >> texture;
            ss >> color;
            uint16_t bagId = stringToId(texture, color);

            containedIn[bagId].push_back(parrent);
            contains[parrent].push_back(bagRule(num, bagId));

            ss >> token; // "bag(s),."s"
            if (token.back() == '.')
                break;
        }
	}

    std::unordered_set<uint16_t> bagsContainingMine;
    texture = "shiny";
    color = "gold";
    calculatePart1(containedIn, bagsContainingMine, stringToId(texture, color));
    std::cout << "Kofera u koji ide moj kofer: " << bagsContainingMine.size() << std::endl;

    int sum = calculatePart2(contains, stringToId(texture, color)) - 1; // -1 to exclude mmy bag
    std::cout << "Ukupno kofera u mom koferu: " << sum << std::endl;

    return 0;
}