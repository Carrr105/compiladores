
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void createCodeEntry(entry_p des,enum operatorTypes op,entry_p arg1,entry_p arg2,int linenum){
 	entry_c temp = (entry_c) malloc(sizeof(codeEntry));
	temp->dest = des;
	temp->op = op;
	temp->arg1 = arg1;
	temp->arg2 = arg2;
	temp->linenum = linenum;
	g_ptr_array_add(codeArray,(gpointer) temp);
	cline++;
}

char * opType(enum operatorTypes a){
  switch (a) {
    case ADDOP:         return "+";
    case SUBOP:         return "-";
    case MULOP:         return "*";
    case DIVOP:         return "/";
    case LTOP:          return "<";
    case EQOP:          return "==";
    case GOTO:          return "JUMP";
    case ASSIGNOP:      return ":=";
    case READOP:        return "READ";
    case WRITEOP:       return "WRITE";
    default:            return "ERROR";
  }
}

void getCodeEntry(){
	return;
}