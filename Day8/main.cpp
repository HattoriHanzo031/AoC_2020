#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

static int pc;
static int accumulator;

enum InstType {
    ACC,
    JMP,
    NOP
};

struct Instruction {
    Instruction(std::string line) : 
        accInc(0),
        pcInc(1),
        executed(false)
    {
        std::stringstream ss(line);
        std::string inst;
        ss >> inst;
        ss >> param;

        if (inst == "acc") {
            type = ACC;
            accInc = param;
        } else if (inst == "jmp") {
            type = JMP;
            pcInc = param;
        } else {
            type = NOP;
        }
    }

    bool execute()
    {
        if (executed)
            return false;

        pc += pcInc;
        accumulator += accInc;
        executed = true;

        return true;
    }

    InstType type;
    int param;
    int accInc;
    int pcInc;
    bool executed;
};

int main()
{
    std::ifstream file("Day8/input.txt");
	std::string line;
    std::vector<Instruction> program;

    if (!file.is_open()) {
        return -1;
    }

	while (getline(file, line)) {
        program.push_back(Instruction(line));
	}

    while (program[pc].execute()) {
        if (pc >= (int)program.size()) {
            std::cout << "Program exited. Accumulator value: " << accumulator << std::endl;
            return 0;
        }
    }

    std::cout << "Accumulator value: " << accumulator << std::endl;
    return 0;
}