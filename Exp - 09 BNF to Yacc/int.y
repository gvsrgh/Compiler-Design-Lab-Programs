%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declare `yyin` to avoid undeclared error
extern FILE *yyin;

struct quad {
    char op[5], arg1[10], arg2[10], result[10];
} QUAD[30];

struct stack {
    int items[100], top;
} stk;

int Index = 0, tIndex = 0, StNo, Ind, tInd;
extern int LineNo;

// Declare `yylex()` properly
int yylex();
void yyerror(const char *s);

// Ensure functions are defined properly
void push(int data);
int pop();
void AddQuadruple(char op[], char arg1[], char arg2[], char result[]);

%}

%union { char var[10]; }
%token <var> NUM VAR RELOP
%token MAIN IF ELSE WHILE TYPE
%type <var> EXPR ASSIGNMENT CONDITION IFST ELSEST WHILELOOP
%left '-' '+'
%left '*' '/'

%%

PROGRAM : MAIN BLOCK { printf("\nProgram recognized correctly!\n"); };

BLOCK : '{' CODE '}' { printf("\nBlock recognized!\n"); };

CODE : CODE STATEMENT 
     | STATEMENT 
     { printf("\nCode detected!\n"); };

STATEMENT : DESCT ';' 
          | ASSIGNMENT ';' 
          | CONDST 
          | WHILEST 
          { printf("\nStatement detected!\n"); };

DESCT : TYPE VARLIST { printf("\nDeclaration detected!\n"); };

VARLIST : VAR ',' VARLIST | VAR { printf("\nVariable detected!\n"); };

ASSIGNMENT : VAR '=' EXPR { printf("\nAssignment detected!\n"); };

EXPR : EXPR '+' EXPR { AddQuadruple("+", $1, $3, $$); }
     | EXPR '-' EXPR { AddQuadruple("-", $1, $3, $$); }
     | EXPR '*' EXPR { AddQuadruple("*", $1, $3, $$); }
     | EXPR '/' EXPR { AddQuadruple("/", $1, $3, $$); }
     | '-' EXPR { AddQuadruple("UMIN", $2, "", $$); }
     | '(' EXPR ')' { strncpy($$, $2, sizeof($$)); }
     | VAR | NUM { printf("\nNumber/Variable Detected!\n"); };

CONDST : IFST {
    Ind = pop();
    sprintf(QUAD[Ind].result, "%d", Index);
    Ind = pop();
    sprintf(QUAD[Ind].result, "%d", Index);
} | IFST ELSEST;

IFST : IF '(' CONDITION ')' {
    strncpy(QUAD[Index].op, "==", sizeof(QUAD[Index].op));
    strncpy(QUAD[Index].arg1, $3, sizeof(QUAD[Index].arg1));
    strncpy(QUAD[Index].arg2, "FALSE", sizeof(QUAD[Index].arg2));
    strncpy(QUAD[Index].result, "-1", sizeof(QUAD[Index].result));
    push(Index);
    Index++;
} BLOCK {
    strncpy(QUAD[Index].op, "GOTO", sizeof(QUAD[Index].op));
    strncpy(QUAD[Index].result, "-1", sizeof(QUAD[Index].result));
    push(Index);
    Index++;
};

ELSEST : ELSE {
    tInd = pop();
    Ind = pop();
    push(tInd);
    sprintf(QUAD[Ind].result, "%d", Index);
} BLOCK {
    Ind = pop();
    sprintf(QUAD[Ind].result, "%d", Index);
};

CONDITION : VAR RELOP VAR { AddQuadruple($2, $1, $3, $$); StNo = Index - 1; } | VAR | NUM;

WHILEST : WHILELOOP {
    Ind = pop();
    sprintf(QUAD[Ind].result, "%d", StNo);
    Ind = pop();
    sprintf(QUAD[Ind].result, "%d", Index);
};

WHILELOOP : WHILE '(' CONDITION ')' {
    strncpy(QUAD[Index].op, "==", sizeof(QUAD[Index].op));
    strncpy(QUAD[Index].arg1, $3, sizeof(QUAD[Index].arg1));
    strncpy(QUAD[Index].arg2, "FALSE", sizeof(QUAD[Index].arg2));
    strncpy(QUAD[Index].result, "-1", sizeof(QUAD[Index].result));
    push(Index);
    Index++;
} BLOCK {
    strncpy(QUAD[Index].op, "GOTO", sizeof(QUAD[Index].op));
    strncpy(QUAD[Index].result, "-1", sizeof(QUAD[Index].result));
    push(Index);
    Index++;
};

%%

int main() {
    FILE *fp;
    int i;

    // Automatically open "test.c" for parsing
    fp = fopen("test.c", "r");
    if (!fp) {
        printf("\n File test.c not found");
        exit(0);
    }
    yyin = fp;

    yyparse();

    printf("\n\n\t\t ----------------------------\n\t\t Pos Operator Arg1 Arg2 Result\n\t\t --------------------");
    for (i = 0; i < Index; i++) {
        printf("\n\t\t %d\t %s\t %s\t %s\t %s", i, QUAD[i].op, QUAD[i].arg1, QUAD[i].arg2, QUAD[i].result);
    }
    printf("\n\t\t -----------------------\n\n");

    fclose(fp);
    return 0;
}

void yyerror(const char *s) {
    printf("\n Syntax Error: %s on line %d", s, LineNo);
}