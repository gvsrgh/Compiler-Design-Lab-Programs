# Lexical Analyzer for C Code

## 📋 Overview
This project implements a lexical analyzer using Lex. The analyzer reads a C program and categorizes its components like keywords, operators, identifiers, string literals, etc.

---

## ✅ Prerequisites

Before you begin, ensure you have the following installed:

1. **Flex** (Fast Lexical Analyzer):
   - Install Flex using your package manager:
     - On Ubuntu/Debian:  
       ```bash
       sudo apt install flex
       ```
     - On macOS (using Homebrew):  
       ```bash
       brew install flex
       ```
     - On Windows: Download the Flex binaries or use Cygwin/WSL.

2. **GCC Compiler**:
   - Install GCC if not already available:
     - On Ubuntu/Debian:  
       ```bash
       sudo apt install build-essential
       ```
     - On macOS (via Xcode Command Line Tools):  
       ```bash
       xcode-select --install
       ```
     - On Windows: Use MinGW or WSL.

3. **Basic Text Editor**:
   - Use any text editor like VS Code, Sublime Text, or Vim to write the Lex and input files.

4. **Test C File**:
   - Create a C file (e.g., `U.c`) that you want to analyze.

---

## 🚀 How to Run

### 1. Write the Lex file
- Create a file named `file_name.l` with the Lex code for the lexical analyzer.  
  Example content for the Lex file is provided below.

### 2. Generate the Lexer
- Run the following command to process the Lex file:
  ```bash
  lex file_name.l
  ```

### 3. Compile the Generated Code
- Compile the `lex.yy.c` file using GCC:
  ```bash
  gcc lex.yy.c -o file_name -lfl
  ```

### 4. Execute the Lexical Analyzer
- Run the compiled program with the input C file:
  ```bash
  ./file_name U.c
  ```

- Replace `U.c` with the name of the C program you want to analyze.

---

## 📂 Example Lex File (`file_name.l`)

Here’s an example `file_name.l` that tokenizes a C program:

```lex
%{
#include <stdio.h>
#include <stdlib.h>

char *word[] = {"keyword", "identifier", "operator", "preprocessor", "comment", "invalid literal", "reserved", "number", "string"};

void display(int);
%}

keyword   "int"|"char"|"short"|"void"|"long"|"if"|"else"|"case"|"for"|"do"|"while"|"break"|"auto"|"static"|"const"|"enum"|"struct" 
reserved  "main"|"FILE"|"printf"|"scanf"|"puts"|"putc"|"getc"|"pow"
comments  "//".*|"/\\*".*"\\*/"
operator  "."|"{"|"}"|"("|")"|"["|"]"|"->"|"+"|"-"|"*"|"/"|"|"|"="|"+="|"-="|"*="|"/="|"%="|"&&"|"||"|"!"|"~"|";"
preprocessor  "#".*
string    "\"".*"\""
identifier  [a-zA-Z_][a-zA-Z0-9_]*
number    [0-9]+(\.[0-9]+)?
%%
{comments}   { display(4); }
{preprocessor}   { display(3); }
{reserved}   { display(6); }
{keyword}    { display(0); }
{operator}   { display(2); }
{string}     { display(8); }
{identifier} { display(1); }
{number}     { display(7); }
[\n\t' ']    {};  // ignore whitespace characters
.            { display(5); }  // invalid literal for anything else
%%
void display(int n) {
    printf("\n%s --> %s\n", yytext, word[n]);
}

int yywrap() {
    return 1;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            printf("Could not open %s \n", argv[1]);
            exit(0);
        }
    }
    yylex();
    return 0;
}
```

---

## 📂 Example C Input File (`U.c`)

Here’s a sample `U.c` file to analyze:
```c
#include<stdio.h>
int main() {
    printf("Hello World!!!");
    return 0;
}
```

---

## 🛠 Explanation of Commands

### 🔹 `lex file_name.l`
- This generates the `lex.yy.c` file, which contains the C code for the lexical analyzer based on your Lex rules.

### 🔹 `gcc lex.yy.c -o file_name -lfl`
- Compiles the generated C code (`lex.yy.c`) into an executable named `file_name`.
- The `-lfl` flag links the Flex library required for the lexical analyzer.

### 🔹 `./file_name U.c`
- Executes the lexical analyzer program with the input C file `U.c`.  
- The analyzer will tokenize and categorize the contents of `U.c`.

---

## 📂 Example Output

For the input `U.c`, the output may look like this:
```
# --> preprocessor
include --> identifier
<stdio.h> --> identifier
int --> keyword
main --> reserved
( --> operator
) --> operator
{ --> operator
printf --> reserved
"Hello World!!!" --> string
; --> operator
return --> keyword
0 --> number
; --> operator
} --> operator
```

---

## 📚 Additional Notes
1. You can analyze other C files by replacing `U.c` with the desired file name.
2. Ensure the Lex file (`file_name.l`) is well-structured and matches your lexical analysis needs.

Feel free to extend the analyzer for additional features like error handling or more token categories!
