#include <iostream>
#include <fstream>
#include <vector>
#include <map>

int sumGroupAnswers(std::vector<std::string>& answers) {
    std::map<char, unsigned> numAnswers; // number of answers for each question
    int everyoneAnswered = 0;

    for (auto answer : answers) {
        for (char c : answer) {
            unsigned num = ++numAnswers[c];     // increase number of answers for this question
            if (num == answers.size()) { // if (num == 1) { // Part 1
                everyoneAnswered++;  // everyone answered this question
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

    std::cout << "Ukupno: " << sum << std::endl;
    return 0;
}