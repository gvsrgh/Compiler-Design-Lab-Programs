%{
    #include <stdio.h>
    int result = 0;
%}

pattern a[a|b]*[\n]

%%

{pattern} { printf("String is valid \n"); }

. { printf("String is not valid \n"); }

%%

int yywrap() {
    return 1;
}


int main() 
{
    printf("Enter the String to Automata: ");
    yylex();
}
