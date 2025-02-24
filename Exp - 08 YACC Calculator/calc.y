%{ 
   /* Definition section */ 
  #include<stdio.h> 
  #include<stdlib.h> 
  int flag=0; 
  int yylex(); // Function prototype for lexer
  void yyerror(const char *s); // Error handling
%} 
   
%token NUMBER 

%left '+' '-' 
%left '*' '/' '%' 
%left '(' ')' 

%% 
ArithmeticExpression: E { 
         printf("\nResult = %d\n", $$); 
         return 0; 
}; 

E: E '+' E { $$ = $1 + $3; } 
 | E '-' E { $$ = $1 - $3; } 
 | E '*' E { $$ = $1 * $3; } 
 | E '/' E { 
      if ($3 == 0) {
         yyerror("Division by zero!");
         exit(1);
      } 
      $$ = $1 / $3; 
   }
 | E '%' E { $$ = $1 % $3; } 
 | '(' E ')' { $$ = $2; } 
 | NUMBER { $$ = $1; } 
; 

%% 

// Driver Code 
int main() 
{ 
   printf("\nEnter an arithmetic expression (use +, -, *, /, %, and parentheses):\n"); 
   yyparse(); 
   if(flag==0) 
      printf("\nEntered arithmetic expression is Valid\n\n"); 
   return 0;
} 

void yyerror(const char *s) 
{ 
   printf("\nError: %s\n", s); 
   flag=1; 
}
