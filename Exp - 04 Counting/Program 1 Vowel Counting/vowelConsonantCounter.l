%{
#include <stdio.h>
#include <stdlib.h>

// Counters for vowels and consonants
int vowels = 0;
int cons = 0;
%}

%%
[aeiouAEIOU]   { vowels++; }   // Matches vowels
[a-zA-Z]       { cons++; }     // Matches consonants
[ \t\n]+       { /* Ignore whitespace, tabs, and newlines */ }
.              { /* Ignore other characters */ }
%%

int yywrap() {
    return 1; // Indicates end of input
}

int main() {
    printf("Enter the string (end input with Ctrl+D):\n");

    // Call the lexer
    yylex();

    // Print results
    printf("\nNumber of vowels = %d\n", vowels);
    printf("Number of consonants = %d\n", cons);

    return 0;
}
