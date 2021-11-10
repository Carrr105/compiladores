using namespace std;
#include <vector>
#include <stack>
#include <map>
#include <string>

#include "frame.h"
#include "instruction.h"
#include "operand.h"

//Singleton class
class VirtualMachine{
private:
	stack<Frame*> frameStack;
	map<string, Frame*> frameMap;
	void loadInstructions(const char* bytecodeFileName);
public:
	vector<Instruction>::iterator instructionPos;
	VirtualMachine(const char* bytecodeFileName);
	~VirtualMachine();
	void runFrame(string frameName, map<string, Operand*> *callArgs);
	void frameReturn(Operand &op);
	void deleteTopFrame();
	void run();
};

VirtualMachine::VirtualMachine(const char* bytecodeFileName){
	loadInstructions(bytecodeFileName);
}

VirtualMachine::~VirtualMachine(){
	for(auto it = frameMap.begin(); it != frameMap.end(); it++){
		delete it->second;
	}
	while(!frameStack.empty()){
		delete frameStack.top();
		frameStack.pop();
	}
}

void VirtualMachine::loadInstructions(const char* bytecodeFileName){
    //Loading bytecode file to instructions list
    ifstream bytecodeFile;
    bytecodeFile.open(bytecodeFileName, ios::in);
    if(bytecodeFile.is_open()){
    	Frame* curFrame = NULL;
        string line;
        while(getline(bytecodeFile, line)){
            //Use token ' ' split line
            bool isCommand = true;
            vector<string> opStrList;
            string command;
            size_t pos = 0;
            while((pos = line.find(" ")) != string::npos){
                string token = line.substr(0, pos);
                line.erase(0, pos + 1);
                if(isCommand){
                    command = token;
                    isCommand = false;
                }else{
                    opStrList.push_back(token);
                }
            }
            if(isCommand){
                command = line;
            }else{
                opStrList.push_back(line);
            }

            auto res = find(Instruction::INSTRUCTION_LIST, Instruction::INSTRUCTION_LIST + 19, command);
            if(res != Instruction::INSTRUCTION_LIST + 19){
            	int commandIndex = res - Instruction::INSTRUCTION_LIST;
            	Instruction ins(commandIndex, opStrList);
            	curFrame->pushInstruction(ins);
            }else{
            	curFrame = new Frame(command.c_str(), opStrList,
            		[this](string frameName, map<string, Operand*> *callArgs){return this->runFrame(frameName, callArgs);},
            		[this](Operand &op){return this->frameReturn(op);},
            		[this](){return this->deleteTopFrame();});
            	frameMap[curFrame->getName()] = curFrame;
            }
        }
        vector<string> opStrList;
        frameMap["print"] = new Frame("print", opStrList,
                    [this](string frameName, map<string, Operand*> *callArgs){return this->runFrame(frameName, callArgs);},
                    [this](Operand &op){return this->frameReturn(op);},
                    [this](){return this->deleteTopFrame();});
    }else{
        string err("Cannot open bytecode file: ");
        err.append(bytecodeFileName);
        cout << err << endl;
        throw err.c_str();
    }
    return ;
}

void VirtualMachine::runFrame(string frameName, map<string, Operand*> *callArgs){
	Frame *curFrame = new Frame();
	*curFrame = (*frameMap[frameName]);

	curFrame->setVariableMap(callArgs);

    if(frameName == "print"){
        curFrame->run_print();
    }else{
        frameStack.push(curFrame);
        frameStack.top()->run();
    }
}

void VirtualMachine::frameReturn(Operand &op){
	Frame *tmp = frameStack.top();
	frameStack.pop();
	if(!frameStack.empty()){
		frameStack.top()->pushOperand(op);
	}
	frameStack.push(tmp);
}

void VirtualMachine::deleteTopFrame(){

	delete frameStack.top();
	frameStack.pop();
}

void VirtualMachine::run(){
	if(frameMap.find("main") != frameMap.end()){
		runFrame(string("main"), NULL);
	}else{
		string err("main function not found.");
        cout << err << endl;
        throw err.c_str();
	}

    return ;
}