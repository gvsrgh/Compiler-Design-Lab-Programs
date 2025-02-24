%{ 
   /* Definition section */ 
  #include<stdio.h> 
  #include<stdlib.h>
  #include "y.tab.h" 
  extern int yylval; 
%} 

%% 
[0-9]+ { 
    yylval = atoi(yytext); 
    return NUMBER; 
} 

[\t] ;  // Ignore tabs

[\n] return 0; // End of input

. return yytext[0]; // Return other characters as-is

%% 

int yywrap() { return 1; }
