#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <sstream>

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

void calculate(std::map<uint16_t, std::vector<uint16_t>>& containedIn, std::set<uint16_t>& out, uint16_t currentId)
{
    auto parrents = containedIn[currentId];
    for (auto parrent : parrents) {
        out.insert(parrent);
        calculate(containedIn, out, parrent);
    }
}

int main()
{
    std::ifstream file("Day7/input.txt");
	std::string line;
    std::string texture;
    std::string color;
    std::map<uint16_t, std::vector<uint16_t>> containedIn;
    std::set<uint16_t> out;

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

            ss >> texture;
            ss >> color;
            uint16_t bagId = stringToId(texture, color);

            containedIn[bagId].push_back(parrent);

            ss >> token; // "bag(s),."s"
            if (token.back() == '.')
                break;
        }
	}

    texture = "shiny";
    color = "gold";
    calculate(containedIn, out, stringToId(texture, color));

    std::cout << "Ukupno: " << out.size() << std::endl;
    return 0;
}