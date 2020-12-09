#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

class Instruction {
public:
    // Enum used for optimisation (it is faster to check int than string)
    enum InstType {
        ACC,
        JMP,
        NOP
    };

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

    bool execute(int& pc, int& accumulator)
    {
        if (executed)
            return false;

        pc += pcInc;
        accumulator += accInc;
        executed = true;

        return true;
    }

    InstType inline getType() const 
    {
        return type;
    }

    // change the type of the instruction and recalculate parameters
    void updateType(InstType t)
    {
        type = t;
        accInc = 0;
        pcInc = 1;

        if (t == ACC)
            accInc = param;
        else if(t == JMP)
            pcInc = param;
    }

    // reset the executed state of the instruction
    void inline reset()
    {
        executed = false;
    }

private:
    InstType type;
    int param;
    int accInc;     // instruction will increment Accumulator by this amount
    int pcInc;      // instruction will increment Program counter by this amount
    bool executed;  // instruction was executed before
};

void resetProgram(std::vector<Instruction>& program, int& pc, int& accumulator)
{
    pc = 0;
    accumulator = 0;
    for (auto i=program.begin(); i!=program.end(); i++)
        i->reset();
}

int main()
{
    std::ifstream file("Day8/input.txt");
    std::string line;
    std::vector<Instruction> program;

    int pc = 0; // index of the next instrution that will be executed (program counter)
    int accumulator = 0;

    if (!file.is_open()) {
        return -1;
    }

    while (getline(file, line)) {
        program.push_back(Instruction(line));
    }

    while (program[pc].execute(pc, accumulator));
    std::cout << "Accumulator value when entering loop: " << accumulator << std::endl;

    // Try fixing the program
    for (auto instrution=program.begin(); instrution!=program.end(); instrution++) {
        // Exchange JMP and NOP
        if (instrution->getType() == Instruction::JMP)
            instrution->updateType(Instruction::NOP);
        else if (instrution->getType() == Instruction::NOP)
            instrution->updateType(Instruction::JMP);
        else
            continue; // not JMP or NOP so go to next instruction

        while (program[pc].execute(pc, accumulator)) {
            if (pc >= (int)program.size()) {
                std::cout << "Program exited with accumulator value: " << accumulator << std::endl;
                return 0;
            }
        }

        // This instruction was not the problem, change it back
        if (instrution->getType() == Instruction::JMP)
            instrution->updateType(Instruction::NOP);
        else
            instrution->updateType(Instruction::JMP);
        resetProgram(program, pc, accumulator);
    }

    std::cout << "No change worked!" << std::endl;
    return -1;
}