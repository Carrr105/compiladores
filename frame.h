using namespace std;
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <fstream>
#include <string>
#include <functional>

#include "macros.h"
#include "instruction.h"
#include "operand.h"

#define FRAME_CALCULATION(name, operation) void Frame::name(){\
    Operand op1 = stack.top(); stack.pop();\
    Operand op2 = stack.top(); stack.pop();\
    if(op1.type == OP_TYPE::DOUBLE && op2.type == OP_TYPE::DOUBLE){\
        OP_VALUE result;\
        result.d = op2.value.d operation op1.value.d;\
        Operand resultOp(OP_TYPE::DOUBLE, result);\
        stack.push(resultOp);\
    }else if(op1.type == OP_TYPE::DOUBLE && op2.type == OP_TYPE::INT){\
        OP_VALUE result;\
        result.d = (double)(op2.value.i operation op1.value.d);\
        Operand resultOp(OP_TYPE::DOUBLE, result);\
        stack.push(resultOp);\
    }else if(op1.type == OP_TYPE::INT && op2.type == OP_TYPE::DOUBLE){\
        OP_VALUE result;\
        result.d = (double)(op2.value.d operation op1.value.i);\
        Operand resultOp(OP_TYPE::DOUBLE, result);\
        stack.push(resultOp);\
    }else if(op1.type == OP_TYPE::INT && op2.type == OP_TYPE::INT){\
        OP_VALUE result;\
        result.i = op2.value.i operation op1.value.i;\
        Operand resultOp(OP_TYPE::INT, result);\
        stack.push(resultOp);\
    }else{\
        OP_VALUE result;\
        result.i = 0;\
        Operand resultOp(OP_TYPE::INT, result);\
        stack.push(resultOp);}\
    instructionPos++; return ;}

#define FRAME_COMPARISON(name, operation) void Frame::name(){\
    Operand op1 = stack.top(); stack.pop();\
    Operand op2 = stack.top(); stack.pop();\
    OP_VALUE result;\
    if(op1.type == OP_TYPE::DOUBLE && op2.type == OP_TYPE::DOUBLE){\
        result.b = op2.value.d operation op1.value.d;\
    }else{\
        result.b = op2.value.i operation op1.value.i;\
    }\
    Operand resultOp(OP_TYPE::BOOL, result);\
    stack.push(resultOp);\
    instructionPos++; return ;}

class Frame{
private:
    string frameName = "";
    vector<string> functionArgumentsName;
    vector<Instruction> instructions;
    stack<Operand> stack;
    map<string, Operand*> *variable_map = NULL;
    vector<Instruction>::iterator instructionPos;
    function<void(string, map<string, Operand*> *)> vmRunFrameCallBack;
    function<void(Operand&)> vmFrameReturnCallBack;
    function<void(void)> vmDeleteTopFrameCallBack;

    void runInstruction(Instruction &curInstruction);
    void LDV(Instruction &ins);
    void LDC(Instruction &ins);
    void HALT(Instruction &ins);
    void CALL(Instruction &ins);
    void RET();
    void ADD();
    void SUB();
    void MUL();
    void DIV();
    void GT();
    void GE();
    void LT();
    void LE();
    void EQ();
    void NEQ();
    void JMP(Instruction &ins);
    void JZ(Instruction &ins);
    void ASN(Instruction &ins);
    void DUP();
public:
    Frame();
    Frame(string frameName, vector<string> functionArgumentsName,
        function<void(string, map<string, Operand*> *)> vmRunFrameCallBack,
        function<void(Operand&)> vmReturnCallBack,
        function<void(void)> vmDeleteTopFrameCallBack);
    Frame(const Frame &frame);
    ~Frame();
    void pushInstruction(Instruction &ins);
    void pushOperand(Operand &op);
    void run_print();
    string getName();
    void setVariableMap(map<string, Operand*> *callArgs);
    void run();
    bool operator < (const Frame & cmp) const;
};

Frame::Frame(){

}

Frame::~Frame(){
    if(variable_map != NULL){
        for(auto it = (*variable_map).begin(); it != (*variable_map).end(); it++){
            ::operator delete(it->second);
        }
        delete variable_map;
    }
}

Frame::Frame(string frameName, vector<string> functionArgumentsName,
        function<void(string, map<string, Operand*> *)> vmRunFrameCallBack,
        function<void(Operand&)> vmReturnCallBack,
        function<void(void)> vmDeleteTopFrameCallBack){
    this->frameName = frameName;
    this->vmRunFrameCallBack = vmRunFrameCallBack;
    this->vmFrameReturnCallBack = vmReturnCallBack;
    this->vmDeleteTopFrameCallBack = vmDeleteTopFrameCallBack;
    this->functionArgumentsName = functionArgumentsName;
}

Frame::Frame(const Frame &frame){
    frameName = frame.frameName;
    for(auto it = frame.instructions.begin(); it != frame.instructions.end(); it++){
        instructions.push_back(*it);
        cout << (instructions.end() - 1)->getCommandIndex() << endl;
    }
    instructionPos = instructions.begin();
}


void Frame::runInstruction(Instruction &curInstruction){
    switch(curInstruction.getCommandIndex()){
        case(0): LDV(curInstruction); break;
        case(1): LDC(curInstruction); break;
        case(2): HALT(curInstruction); break;
        case(3): CALL(curInstruction); break;
        case(4): RET(); break;
        case(5): ADD(); break;
        case(6): SUB(); break;
        case(7): MUL(); break;
        case(8): DIV(); break;
        case(9): GT(); break;
        case(10): GE(); break;
        case(11): LT(); break;
        case(12): LE(); break;
        case(13): EQ(); break;
        case(14): NEQ(); break;
        case(15): JMP(curInstruction); break;
        case(16): JZ(curInstruction); break;
        case(17): ASN(curInstruction); break;
        case(18): DUP(); break;
        default: HALT(curInstruction); break;
    }
}


void Frame::LDV(Instruction &ins){
    stack.push(*(*variable_map)[ins.getOpStrList()[0]]);
    instructionPos++;
}


void Frame::LDC(Instruction &ins){

    Operand operand(ins.getCommandIndex(), ins.getOpStrList());
    stack.push(operand);

    instructionPos++;
    return ;
}


void Frame::HALT(Instruction &ins){
    exit(0);
}


void Frame::CALL(Instruction &ins){
    map<string, Operand*> *callArgs = new map<string, Operand*>();
    int argn = stoi(ins.getOpStrList()[1]);
    for(int i = 0; i < argn; i++){
        (*callArgs)[to_string(i)] = new Operand(stack.top());
        stack.pop();
    }
    // Run new frame by VM callback function
    vmRunFrameCallBack(ins.getOpStrList()[0], callArgs);

    if(ins.getOpStrList()[0] != "print"){
        vmDeleteTopFrameCallBack();
    }
    instructionPos++;
}

void Frame::RET(){
    Operand op = stack.top();
    stack.pop();
    vmFrameReturnCallBack(op);
    instructionPos = instructions.end();
}


FRAME_CALCULATION(ADD, +)
FRAME_CALCULATION(SUB, -)
FRAME_CALCULATION(MUL, *)
FRAME_CALCULATION(DIV, /)

FRAME_COMPARISON(GT, >)
FRAME_COMPARISON(GE, >=)
FRAME_COMPARISON(LT, <)
FRAME_COMPARISON(LE, <=)
FRAME_COMPARISON(EQ, ==)
FRAME_COMPARISON(NEQ, !=)


void Frame::JMP(Instruction &ins){
    int des = stoi(ins.getOpStrList()[0]);
    instructionPos = instructions.begin() + des;
    return ;
}


void Frame::JZ(Instruction &ins){
    Operand op = stack.top();
    stack.pop();
    if(op.type != OP_TYPE::BOOL){
        string err("Type maching error!");
        cout << err << endl;
        throw err.c_str();
    }else{
        if(op.value.b){
            instructionPos++;
        }else{
            int des = stoi(ins.getOpStrList()[0]);
            instructionPos = instructions.begin() + des;
        }
    }
    return ;
}


void Frame::ASN(Instruction &ins){
    if(variable_map == NULL){
        variable_map = new map<string, Operand*>();
    }
    (*variable_map)[ins.getOpStrList()[0]] =  new Operand(stack.top());
    stack.pop();

    instructionPos++;
    return ;
}

void Frame::DUP(){

    stack.push(stack.top());

    instructionPos++;
    return ;
}


void Frame::run_print(){

    for(int i = 0; i < variable_map->size(); i++){
        LOG_OPERAND((*((*variable_map)[to_string(i)])))
        cout << endl;
    }
    return ;
}

void Frame::pushInstruction(Instruction &ins){
    this->instructions.push_back(ins);
}

string Frame::getName(){
    return this->frameName;
}

void Frame::setVariableMap(map<string, Operand*> *callArgs){
    if(callArgs != NULL){
        if(frameName == "print"){
            variable_map = callArgs;
        }else{
            map<string, Operand*> *tmp = new map<string, Operand*>();
            for(auto it = callArgs->begin(); it != callArgs->end(); it++){
                (*tmp)[functionArgumentsName[stoi(it->first)]] = new Operand(it->second->type, it->second->value);
            }
            variable_map = tmp;

            // callArgs map now useless, delete it
            for(auto it = (*callArgs).begin(); it != (*callArgs).end(); it++){
                ::operator delete(it->second);
            }
            delete callArgs;
        }
    }
}

bool Frame::operator < (const Frame & cmp) const{
    return frameName < cmp.frameName;
}

void Frame::run(){
    instructionPos = instructions.begin();
    while(instructionPos != instructions.end()){

        #ifdef __LUNA__DEBUG
        RUN_AND_LOG_INSTRUCTION((*instructionPos));
        #endif
        #ifndef __LUNA__DEBUG
        runInstruction(*instructionPos);
        #endif
    }
}

void Frame::pushOperand(Operand &op){
    stack.push(op);
}