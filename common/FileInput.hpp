#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class FileInput {
public:
	FileInput(std::string fileName, char sep = '\n');
	void setSeparator(char sep);
	bool resetInput();
	bool getInput(std::vector<std::string>& input);
	bool getInput(std::vector<int>& input);
	bool getNext(std::string& nextInput);
	bool getNext(int& input);
private:
	char separator;
	std::ifstream file;
};
