#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

typedef void (*operation) (int param);

static int pc;
static int accumulator;

class instruction {
    operation op;
    int param;
    bool executed;

    static void acc(int param)
    {
        accumulator += param;
        pc++;
    }

    static void jmp(int param)
    {
        pc += param;
    }

    static void nop(int param)
    {
        (void) param;
        pc++;
    }

    static inline const std::map<std::string, operation> operationsMap = {
        {"acc", acc},
        {"jmp", jmp},
        {"nop", nop}
    };

public:
    instruction(std::string line) : executed(0)
    {
        std::stringstream ss(line);
        std::string token;
        ss >> token;
        op = operationsMap.find(token)->second;
        ss >> param;
    }

    bool execute()
    {
        if (executed)
            return false;
        
        op(param);
        executed = true;
        return true;
    }

    inline int getNext()
    {
        return pc;
    }

    inline int getAcc()
    {
        return accumulator;
    }
};


int main()
{
    std::ifstream file("Day8/input.txt");
	std::string line;
    std::vector<instruction> program;

    if (!file.is_open()) {
        return -1;
    }

	while (getline(file, line)) {
        program.push_back(instruction(line));
	}
    int nextInstruction = 0;
    while (program[nextInstruction].execute()) {
        nextInstruction = program[nextInstruction].getNext();
        if (nextInstruction >= (int)program.size()) {
            break;
        }
    }

    std::cout << "Accumulator value: " << program[nextInstruction].getAcc() << std::endl;
    return 0;
}