#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Node {
    
    char* identifier;
    char* scope;
    char* type;
    int lineNo;
    Node* next;
  
public:
    Node()
    {
        next = NULL;
    }
  
    Node(char*  key, char*  value, char*  type, int lineNo)
    {
        this->identifier = key;
        this->scope = value;
        this->type = type;
        this->lineNo = lineNo;
        next = NULL;
    }
  
    void print()
    {
        printf("Identifier's Name: %s \n Type: %s \n Scope: %s \n Line Number: %d \n",
                                                                                 identifier, type, scope, lineNo);
    }
    friend class SymT;
};