%{
  #include "SymT.h" 
  extern FILE* yyin;
  int yylex();
  void yyerror(const char *s);
%}


%token PROGRAM VARS IF ELSE PRINT CHAR MAIN FUNCTION COMMA RETURN READ WRITE WHILE GREATEREQUAL
%token INT FLOAT ID SEMICOLON PLUS MINUS DIVIDE MULTIPLY EQUALS QUOTATIONMARK FOR LESSEQUAL
%token OPENPARENTHESES CLOSEPARENTHESES DOT TWODOTS OPENBRACKET CLOSEBRACKET DO AND
%token OPENBRACE CLOSEBRACE DIFFERENT GREATER LESS CTEF CTEI CTESTRING THEN TO OR EQUALS_BOOLEAN
%token <id> IDENT 

%type<id> ID

%start programa

%%

programa:  PROGRAM ID SEMICOLON vars funciones bloque {printf("OK ! Good Grammar\n");}
    | PROGRAM ID SEMICOLON vars bloque
    | PROGRAM ID SEMICOLON funciones bloque 
    | PROGRAM ID SEMICOLON bloque
    ;

bloque: MAIN OPENPARENTHESES CLOSEPARENTHESES OPENBRACE estatuto CLOSEBRACE
    | MAIN OPENPARENTHESES CLOSEPARENTHESES OPENBRACE CLOSEBRACE
    ;

tipo: INT
    | FLOAT
    | CHAR
    ;

funciones: FUNCTION tipo ID OPENPARENTHESES params CLOSEPARENTHESES SEMICOLON
            vars OPENBRACE estatuto CLOSEBRACE
    | FUNCTION ID OPENPARENTHESES params CLOSEPARENTHESES SEMICOLON
            vars OPENBRACE estatuto CLOSEBRACE 
    | FUNCTION tipo ID OPENPARENTHESES CLOSEPARENTHESES SEMICOLON
            vars OPENBRACE estatuto CLOSEBRACE
    | FUNCTION tipo ID OPENPARENTHESES params CLOSEPARENTHESES SEMICOLON
            OPENBRACE estatuto CLOSEBRACE
    | FUNCTION tipo ID OPENPARENTHESES params CLOSEPARENTHESES SEMICOLON
            vars OPENBRACE CLOSEBRACE
    | FUNCTION ID OPENPARENTHESES CLOSEPARENTHESES SEMICOLON
            vars OPENBRACE estatuto CLOSEBRACE
    | FUNCTION ID OPENPARENTHESES params CLOSEPARENTHESES SEMICOLON
            OPENBRACE estatuto CLOSEBRACE
    | FUNCTION ID OPENPARENTHESES params CLOSEPARENTHESES SEMICOLON
            vars OPENBRACE CLOSEBRACE
    | FUNCTION tipo ID OPENPARENTHESES CLOSEPARENTHESES SEMICOLON
            OPENBRACE estatuto CLOSEBRACE
    | FUNCTION tipo ID OPENPARENTHESES CLOSEPARENTHESES SEMICOLON
            vars OPENBRACE CLOSEBRACE
    | FUNCTION tipo ID OPENPARENTHESES params CLOSEPARENTHESES SEMICOLON
            OPENBRACE CLOSEBRACE
    | FUNCTION ID OPENPARENTHESES CLOSEPARENTHESES SEMICOLON
            OPENBRACE estatuto CLOSEBRACE
    | FUNCTION ID OPENPARENTHESES params CLOSEPARENTHESES SEMICOLON
            OPENBRACE CLOSEBRACE
    | FUNCTION tipo ID OPENPARENTHESES CLOSEPARENTHESES SEMICOLON
            OPENBRACE CLOSEBRACE
    | FUNCTION ID OPENPARENTHESES CLOSEPARENTHESES SEMICOLON
            vars OPENBRACE CLOSEBRACE
    | FUNCTION ID OPENPARENTHESES CLOSEPARENTHESES SEMICOLON
            OPENBRACE CLOSEBRACE
    ;

vars: VARS tipo TWODOTS params SEMICOLON
    ;

params: ID {/* install( $1, $<tipo>0 ); */}
        | ID OPENBRACKET paramsP CLOSEBRACKET 
        | ID OPENBRACKET paramsP CLOSEBRACKET COMMA params
        | ID COMMA params
        ;

paramsP: CTEI
        | ID
        | params_index
        ;

params_index: ID
        | ID OPENBRACKET CTEI CLOSEBRACKET
        | ID OPENBRACKET ID CLOSEBRACKET
        | ID OPENBRACKET params_index CLOSEBRACKET
        ;

estatuto: asignacion
        | llamada
        | retorno
        | lectura
        | escritura
        | decision
        | repeticion
        ;

llamada: ID OPENPARENTHESES params CLOSEPARENTHESES SEMICOLON
        | ID OPENPARENTHESES CLOSEPARENTHESES SEMICOLON
        ;

retorno: RETURN OPENPARENTHESES exp CLOSEPARENTHESES SEMICOLON
        ;

lectura: READ OPENPARENTHESES params CLOSEPARENTHESES SEMICOLON
        ;

escritura: WRITE OPENPARENTHESES escrituraP
        ;

escrituraP: QUOTATIONMARK CTESTRING QUOTATIONMARK COMMA escrituraP
        | exp COMMA escrituraP
        | QUOTATIONMARK CTESTRING QUOTATIONMARK CLOSEPARENTHESES SEMICOLON
        | exp CLOSEPARENTHESES SEMICOLON
        ;

decision: IF OPENPARENTHESES exp CLOSEPARENTHESES THEN OPENBRACE estatuto CLOSEBRACE
          ELSE OPENBRACE estatuto CLOSEBRACE
          | IF OPENPARENTHESES exp CLOSEPARENTHESES THEN OPENBRACE CLOSEBRACE
          ELSE OPENBRACE estatuto CLOSEBRACE
          | IF OPENPARENTHESES exp CLOSEPARENTHESES THEN OPENBRACE estatuto CLOSEBRACE
          ELSE OPENBRACE CLOSEBRACE
          | IF OPENPARENTHESES exp CLOSEPARENTHESES THEN OPENBRACE estatuto CLOSEBRACE
          | IF OPENPARENTHESES exp CLOSEPARENTHESES THEN OPENBRACE CLOSEBRACE
          ;

repeticion: condicional
        | no_condicional
        ;

condicional: WHILE OPENPARENTHESES exp CLOSEPARENTHESES DO OPENBRACE estatuto CLOSEBRACE
        | WHILE OPENPARENTHESES exp CLOSEPARENTHESES DO OPENBRACE CLOSEBRACE
        ;

no_condicional: FOR ID EQUALS exp TO exp DO OPENBRACE estatuto CLOSEBRACE
        | FOR ID EQUALS exp TO exp DO OPENBRACE CLOSEBRACE
        ;

asignacion: ID EQUALS exp SEMICOLON
        | ID OPENBRACKET CTEI CLOSEBRACKET EQUALS exp SEMICOLON
        | ID OPENBRACKET ID CLOSEBRACKET EQUALS exp SEMICOLON
        | ID OPENBRACKET params_index CLOSEBRACKET EQUALS exp SEMICOLON
        ;

exp: termino
    | termino PLUS exp {/*
                                        if(($1->type==int) && ($3->type==int)) {
                                            uVal value;
                                            value.i_value = 0;
                                            $$ = createTempConstant(value, int);
                                        }
                                        else if(($1->type==float) && ($3->type==float)) {
                                            uVal value;
                                            value.r_value = 0;
                                            $$ = createTempConstant(value, float);
                                        }
                                        else {
                                            if($$->type == float) {
                                                if(($1->type==float) && ($3->type==float)) {
                                                    uVal value;
                                                    value.r_value = 0;
                                                    $$ = createTempConstant(value, float);
                                                }
                                                else if(($1->type==int) && ($3->type==float)) {
                                                    uVal value;
                                                    value.r_value = 0;
                                                    $$ = createTempConstant(value, float);
                                                }
                                                else {
                                                    printf("Error Line %d: Non compatible types\n" ,yylineno);
                                                    exit(EXIT_FAILURE);
                                                }
                                            }
                                            else {
                                                printf("Error Line %d: Non compatible types\n" ,yylineno);
                                                exit(EXIT_FAILURE);
                                            }
                                        }*/
                                    }
    | termino MINUS exp {/*
                                        if(($1->type==int) && ($3->type==int)) {
                                            uVal value;
                                            value.i_value = 0;
                                            $$ = createTempConstant(value, int);
                                        }
                                        else if(($1->type==float) && ($3->type==float)) {
                                            uVal value;
                                            value.r_value = 0;
                                            $$ = createTempConstant(value, float);
                                        }
                                        else {
                                            if($$->type == float) {
                                                if(($1->type==float) && ($3->type==int)){
                                                    uVal value;
                                                    value.r_value = 0;
                                                    $$ = createTempConstant(value, float);
                                                }
                                                else if(($1->type==int) && ($3->type==float)){
                                                    uVal value;
                                                    value.r_value = 0;
                                                    $$ = createTempConstant(value, float);
                                                }
                                                else{
                                                    printf("Error Line %d: Non compatible types\n" ,yylineno);
                                                    exit(EXIT_FAILURE);
                                                }
                                            }
                                        }*/
                                    }
    ;

termino: factor
    | factor MULTIPLY termino {/*
                                    if(($1->type==int) && ($3->type==int)) {
                                        uVal value;
                                        value.i_value = $1->value.i_value * $3->value.i_value;
                                        $$ = createTempConstant(value, int);
                                    }
                                    else if(($1->type==float) && ($3->type==float)) {
                                        uVal value;
                                        value.r_value = $1->value.r_value * $3->value.r_value;
                                        $$ = createTempConstant(value, float);
                                    }
                                    else {
                                        if(($1->type==float) && ($3->type==int)){
                                            uVal value;
                                            value.r_value = $1->value.r_value * $3->value.i_value;
                                            $$ = createTempConstant(value, float);
                                        }
                                        else if(($1->type==int) && ($3->type==float)){
                                            uVal value;
                                            value.r_value = 0;
                                            value.r_value = $1->value.i_value * $3->value.r_value;
                                            $$ = createTempConstant(value, float);
                                        }
                                        else{
                                            printf("Error %d: Types are not compatible\n" ,yylineno);
                                            exit(EXIT_FAILURE);
                                        }
                                    }*/
                                }
    | factor DIVIDE termino {/*
                                    if(($1->type==int) && ($3->type==int)) {
                                        uVal value;
                                        value.i_value = 0;
                                        if($3->value.i_value == 0){
                                            printf("Error %d: Division by zero\n" ,yylineno);
                                            exit(EXIT_FAILURE);
                                        }
                                        $$ = createTempConstant(value, int);
                                    }
                                    else if(($1->type==float) && ($3->type==float)) {
                                        uVal value;
                                        value.r_value = 0;
                                        if($3->value.r_value == 0.0){
                                            printf("Error Line %d: Division by zero\n" ,yylineno);
                                            exit(EXIT_FAILURE);
                                        }
                                        $$ = createTempConstant(value, float);
                                    }
                                    else {
                                        if(($1->type==float) && ($3->type==int)){
                                            uVal value;
                                            value.r_value = 0;
                                            if($3->value.i_value == 0){
                                                printf("Error %d: Division by zero\n" ,yylineno);
                                                exit(EXIT_FAILURE);
                                            }
                                            $$ = createTempConstant(value, float);
                                        }
                                        else if(($1->type==int) && ($3->type==float)){
                                            uVal value;
                                            value.r_value = 0;
                                            if($3->value.r_value == 0.0){
                                                printf("Error %d: Division by zero\n" ,yylineno);
                                                exit(EXIT_FAILURE);
                                            }
                                            $$ = createTempConstant(value, float);
                                        }
                                        else{
                                            printf("Error %d: Non compatible types\n" ,yylineno);
                                            exit(EXIT_FAILURE);
                                        }
                                      }*/
                                }
    ;

factor: ID OPENPARENTHESES params CLOSEPARENTHESES
    | ID
    | CTEF
    | CTEI
    | OPENPARENTHESES h_exp CLOSEPARENTHESES
    ;

h_exp: s_exp
    | s_exp AND h_exp
    | s_exp OR h_exp
    ;

s_exp: exp
    | exp GREATER exp
    | exp LESS exp
    | exp DIFFERENT exp
    | exp EQUALS_BOOLEAN exp
    | exp LESSEQUAL exp
    | exp GREATEREQUAL exp
    ;

empty:;
    


%%

int main() {
  yyin = fopen("test.txt", "r");
  yyparse();
  fclose(yyin);
  return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}

