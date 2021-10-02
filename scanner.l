%{
    #include "y.tab.h"
%}

%%
program                     return PROGRAM;
VARS                        return VARS;
if                          return IF;
else                        return ELSE;
then                        return THEN;
while                       return WHILE;
for                         return FOR;
do                          return DO;
to                          return TO;
print                       return PRINT;
int                         return INT;
float                       return FLOAT;
char                        return CHAR;
main                        return MAIN;
function                    return FUNCTION;
return                      return RETURN;
read                        return READ;
write                       return WRITE;
[a-zA-Z][a-zA-Z_0-9]*       return ID;
"\""                        return QUOTATIONMARK;
";"                         return SEMICOLON;
"+"                         return PLUS;
"-"                         return MINUS;
"/"                         return DIVIDE;
"*"                         return MULTIPLY;
"="                         return EQUALS;
"("                         return OPENPARENTHESES;
")"                         return CLOSEPARENTHESES;
"."                         return DOT;
":"                         return TWODOTS;
"{"                         return OPENBRACE;
"}"                         return CLOSEBRACE;
"["                         return OPENBRACKET;
"]"                         return CLOSEBRACKET;
"!="                        return DIFFERENT;
"=="                        return EQUALS_BOOLEAN;
">"                         return GREATER;
"<"                         return LESS;
">="                        return GREATEREQUAL;
"<="                        return LESSEQUAL;
","                         return COMMA;
"&&"                        return AND;
"||"                        return OR;
([1-9]|[1-9][0-9]|[1-9][0-9][0-9]|[1-9][0-9][0-9][0-9])        return CTEI;
[+-]?([0-9]*[.])?[0-9]+     return CTEF;
%([^.]+?)%                  return CTESTRING;

[ \t\n]                     ;
%%

int yywrap(void){
    return 1;
}