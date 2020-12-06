#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

#define MAX_QUESTIONS ('z' - 'a' + 1) // number of possible questions

int sumGroupAnswers(std::vector<std::string>& answers) {
    unsigned numAnswers[MAX_QUESTIONS] = {0}; // number of answers for each possible question
    int everyoneAnswered = 0;

    for (auto answer : answers) {
        for (char c : answer) {
            int index = c -'a';
            numAnswers[index]++;
            // if (numAnswers[index] == 1) { // Part 1
            if (numAnswers[index] == answers.size()) { // everyone answered this question
                everyoneAnswered++;
            }
        }
    }
    return everyoneAnswered;
}

int main()
{
    std::ifstream file("Day6/input.txt");
	std::string line;
	long sum = 0;
    std::vector<std::string> groupAnswers; // all answers of a group

	while (getline(file, line)) {
        if (line.size() != 0)
            groupAnswers.push_back(line);

        if (line.size() == 0 || file.peek() == EOF) {
            sum += sumGroupAnswers(groupAnswers);
            groupAnswers.clear();
        }
	}

    std::cout << sum << std::endl;
    return 0;
}