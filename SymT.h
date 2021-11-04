#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "Node.h"

#define MAX 1000

class SymT {
    Node* head[MAX];
  
public:
    SymT()
    {
        for (int i = 0; i < MAX; i++)
            head[i] = NULL;
    }
  
    int hashf(char* id); // hash function
    bool insert(char* id, char* scope,
                char* Type, int lineno);
  
    char* find(char* id);
  
    bool deleteRecord(char* id);
  
    bool modify(char* id, char* scope,
                char* Type, int lineno);
};
  
// Function to modify an identifier
bool SymT::modify(char* id, char* s,
                         char* t, int l) {
    int index = hashf(id);
    Node* start = head[index];
  
    if (start == NULL)
        return "-1";
  
    while (start != NULL) {
        if (start->identifier == id) {
            start->scope = s;
            start->type = t;
            start->lineNo = l;
            return true;
        }
        start = start->next;
    }
  
    return false; // id not found
}
  
// Function to delete an identifier
bool SymT::deleteRecord(char* id)
{
    int index = hashf(id);
    Node* tmp = head[index];
    Node* par = head[index];
  
    // no identifier is present at that index
    if (tmp == NULL) {
        return false;
    }
    // only one identifier is present
    if (tmp->identifier == id && tmp->next == NULL) {
        tmp->next = NULL;
        free (tmp);
        return true;
    }
  
    while (tmp->identifier != id && tmp->next != NULL) {
        par = tmp;
        tmp = tmp->next;
    }
    if (tmp->identifier == id && tmp->next != NULL) {
        par->next = tmp->next;
        tmp->next = NULL;
        free(tmp);
        return true;
    }
  
    // delete at the end
    else {
        par->next = NULL;
        tmp->next = NULL;
        free (tmp);
        return true;
    }
    return false;
}
  
// Function to find an identifier
char* SymT::find(char* id)
{
    int index = hashf(id);
    Node* start = head[index];
  
    if (start == NULL)
        return "-1";
  
    while (start != NULL) {
  
        if (start->identifier == id) {
            start->print();
            return start->scope;
        }
  
        start = start->next;
    }
  
    return "-1"; // not found
}
  
// Function to insert an identifier
bool SymT::insert(char* id, char* scope,
                         char* Type, int lineno)
{
    int index = hashf(id);
    Node* p = new Node(id, scope, Type, lineno);
  
    if (head[index] == NULL) {
        head[index] = p;
        printf ("\n %s inserted", id);
        return true;
    }
  
    else {
        Node* start = head[index];
        while (start->next != NULL)
            start = start->next;
  
        start->next = p;
        printf ("\n %s inserted", id);
        return true;
    }
  
    return false;
}
  
int SymT::hashf(char* id)
{
    int asciiSum = 0;
  
    for (int i = 0; i < strlen(id); i++) {
        asciiSum = asciiSum + id[i];
    }
  
    return (asciiSum % 100);
}