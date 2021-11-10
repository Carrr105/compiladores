using namespace std;
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "macros.h"

class Instruction{
private:
    int commandIndex;
    vector<string> opStrList;
public:
	static string const INSTRUCTION_LIST[];
	Instruction();
	~Instruction();
    Instruction(int commandIndex, vector<string> opStrList);
    Instruction(const Instruction &ins);
    int getCommandIndex();
    vector<string> getOpStrList();
};

//Size 19
string const Instruction::INSTRUCTION_LIST[] =
{"LDV", "LDC", "HALT", "CALL", "RET", "ADD", "SUB", "MUL", "DIV", "GT",
 "GE", "LT", "LE", "EQ", "NEQ", "JMP", "JZ", "ASN", "DUP"};

Instruction::Instruction(){
    
}

Instruction::~Instruction(){

}

Instruction::Instruction(int commandIndex, vector<string> opStrList){
    this->commandIndex = commandIndex;
    for(auto it = opStrList.begin(); it != opStrList.end(); it++){
        this->opStrList.push_back(*it);
    }
}

Instruction::Instruction(const Instruction &ins){
    commandIndex = ins.commandIndex;
    for(auto it = ins.opStrList.begin(); it != ins.opStrList.end(); it++){
        opStrList.push_back(*it);
    }
}

int Instruction::getCommandIndex(){
    return this->commandIndex;
}

vector<string> Instruction::getOpStrList(){
    return this->opStrList;
}