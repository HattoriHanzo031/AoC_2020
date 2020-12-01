#include "FileInput.hpp"


FileInput::FileInput(std::string fileName, char sep) :
	separator(sep) ,
	file(fileName)
{
}

void FileInput::setSeparator(char sep)
{
	this->separator = sep;
}

bool FileInput::getInput(std::vector<std::string>& input)
{
	std::string line;
	
	if (!file.is_open()) {
		std::cout << "File not open";
		return false;
	}
	
	file.clear();
	file.seekg(0);
	
	while (getline(file, line)) {
		input.push_back(line);
	}
	return true;
}

bool FileInput::getInput(std::vector<int>& input)
{
	std::string line;
	
	if (!file.is_open()) {
		std::cout << "File not open";
		return false;
	}
	
	file.clear();
	file.seekg(0);
	
	while (file.peek() != EOF) {
		int num;
		file >> num;
		input.push_back(num);
	}
	return true;
}

bool FileInput::resetInput()
{
	std::string line;
	
	if (!file.is_open()) {
		std::cout << "File not open";
		return false;
	}
	
	file.clear();
	file.seekg(0);
	return true;
}

bool FileInput::getNext(std::string& input)
{
	if (!file.is_open()) {
		std::cout << "File not open";
		return false;
	}

	if (file.peek() == EOF) {
		std::cout << "EOF";
		return false;
	}

	getline(file, input);
	return true;
}

bool FileInput::getNext(int& input)
{
	std::string line;
	if (!file.is_open()) {
		std::cout << "File not open";
		return false;
	}

	if (file.peek() == EOF) {
		std::cout << "EOF";
		return false;
	}
	file >> input;
	return true;
}