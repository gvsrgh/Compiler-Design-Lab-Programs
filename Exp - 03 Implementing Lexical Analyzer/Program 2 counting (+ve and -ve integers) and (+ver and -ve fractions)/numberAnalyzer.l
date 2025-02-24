%{
#include <stdio.h>
#include <stdlib.h>

// Counters for different types of numbers
int posint = 0, negint = 0, posfraction = 0, negfraction = 0;
%}

%%
[-][0-9]+(\.[0-9]+)?   { if (strchr(yytext, '.')) negfraction++; else negint++; }  // Matches negative integers and fractions
[+]?[0-9]+(\.[0-9]+)?  { if (strchr(yytext, '.')) posfraction++; else posint++; }  // Matches positive integers and fractions
[ \t\n]+               { /* Ignore whitespace */ }
.                      { /* Ignore other characters */ }
%%

int yywrap() {
    return 1; // Indicates end of file
}

int main(int argc, char *argv[]) {
    // Check for valid command-line arguments
    if (argc != 2) {
        printf("Usage: <./a.out> <sourcefile>\n");
        exit(0);
    }

    // Open the input file
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        printf("Error: Could not open file %s\n", argv[1]);
        exit(1);
    }

    // Run the lexical analyzer
    yylex();

    // Print the results
    printf("Number of +ve integers = %d\n", posint);
    printf("Number of -ve integers = %d\n", negint);
    printf("Number of +ve fractions = %d\n", posfraction);
    printf("Number of -ve fractions = %d\n", negfraction);

    fclose(yyin); // Close the file
    return 0;
}

