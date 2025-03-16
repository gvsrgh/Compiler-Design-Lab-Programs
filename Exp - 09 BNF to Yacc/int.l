%{
#include "y.tab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>  

int LineNo = 1;
%}

identifier [a-zA-Z][_a-zA-Z0-9]*
number [0-9]+|([0-9]*\.[0-9]+)

%%

main\(\)       { printf("Token: MAIN\n"); return MAIN; }
if             { printf("Token: IF\n"); return IF; }
else           { printf("Token: ELSE\n"); return ELSE; }
while          { printf("Token: WHILE\n"); return WHILE; }
int            { printf("Token: TYPE (int)\n"); return TYPE; }
char           { printf("Token: TYPE (char)\n"); return TYPE; }
float          { printf("Token: TYPE (float)\n"); return TYPE; }

{identifier}   { printf("Token: VAR (%s)\n", yytext); strncpy(yylval.var, yytext, sizeof(yylval.var) - 1); return VAR; }
{number}       { printf("Token: NUM (%s)\n", yytext); strncpy(yylval.var, yytext, sizeof(yylval.var) - 1); return NUM; }
\<|\>|\>=|\<=|== { printf("Token: RELOP (%s)\n", yytext); strncpy(yylval.var, yytext, sizeof(yylval.var) - 1); return RELOP; }

[ \t]+          { printf("Ignoring whitespace\n"); } // Ignore spaces and tabs
\n              { LineNo++; printf("Newline detected\n"); return '\n'; } // Handle new lines properly
.               { printf("Token: '%c'\n", yytext[0]); return yytext[0]; }  // Return single character tokens

%%

int yywrap() { return 1; }