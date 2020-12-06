#include <string.h>
#include <iostream>
#include <fstream>

#define MAX_QUESTIONS ('z' - 'a' + 1)

int main()
{
    std::ifstream file("Day6/input.txt");
    std::string line;
    int sum = 0;
    int numAnswers = 0;
    bool answers[MAX_QUESTIONS] = {0};

	while (getline(file, line)) {
        for (char c : line) {
            unsigned index = c - 'a';
            if (index < MAX_QUESTIONS && answers[index] == false) {
                answers[index] = true;
                numAnswers++;
            }
        }

        if (line.size() == 0 || file.peek() == EOF) {
            sum += numAnswers;
            numAnswers = 0;
            memset(answers, 0, MAX_QUESTIONS);
        }
	}
    std::cout << sum << std::endl;
    return 0;
}