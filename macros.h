using namespace std;

#define LOG(x) cout << x << endl;
#define LOGI(x) cout << x << " ";
#define LOGE(x) cerr << x << endl;

#define LOG_OPERAND(OP) switch(OP.type){\
                            case(OP_TYPE::INT):\
                                cout << OP.value.i;\
                                break;\
                            case(OP_TYPE::DOUBLE):\
                                cout << OP.value.d;\
                                break;\
                            case(OP_TYPE::BOOL):\
                                if(OP.value.b){\
                                    cout << "true";\
                                }else{\
                                    cout << "false";\
                                }\
                                break;\
                            default: break;}

#define RUN_AND_LOG_INSTRUCTION(ins) string line;\
        getline(cin, line);\
        cout << frameName << "(";\
        for(auto it = functionArgumentsName.begin(); it != functionArgumentsName.end(); it++){\
            LOG_OPERAND((*((*variable_map)[*it])))\
            if(it != functionArgumentsName.end() - 1){cout << ", ";}}\
        cout << ") ";\
        cout << instructionPos-instructions.begin() << " ";\
		cout << Instruction::INSTRUCTION_LIST[ins.getCommandIndex()] << " ";\
		if(ins.getCommandIndex() == 3) cout << endl;\
		if(ins.getCommandIndex() == 19) cout << endl;\
		runInstruction(ins);\
        if(instructionPos!=instructions.end()){\
            if(stack.size() != 0 && (instructionPos - 1)->getCommandIndex() != 3){\
                switch(stack.top().type){\
                    case(OP_TYPE::BOOL): {cout<<"bool ";\
                        if(stack.top().value.b){\
                            cout << "true" << endl;\
                        }else{\
                            cout << "false" << endl;\
                        }break;\
                    }\
                    case(OP_TYPE::INT): cout<<"int ";cout << stack.top().value.i << endl; break;\
                    case(OP_TYPE::DOUBLE): cout<<"double ";cout << stack.top().value.d << endl; break;\
                    default: break;\
                }\
            }else if((instructionPos - 1)->getCommandIndex() == 19){}\
             else if((instructionPos - 1)->getCommandIndex() != 3){\
                cout << endl;\
            }\
        }else{\
            cout << endl;}