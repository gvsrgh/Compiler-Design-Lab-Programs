# Lexical Analyzer for Number Categorization 📊

## 📋 Overview
This project implements a Lex-based lexical analyzer that reads a file containing numbers and categorizes them into:
- Positive Integers
- Negative Integers
- Positive Fractions
- Negative Fractions

It uses Lex to tokenize and process the input file, providing a detailed count of each category.

---

## 🚀 How to Run

Follow the steps below to compile and execute the lexical analyzer:

### 1️⃣ Write the Lex File
Save the following code into a file named `numberAnalyzer.l`:

```c
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
```

---

### 2️⃣ Compile the Lex File
Run the following command to process the Lex file and generate a C program (`lex.yy.c`):
```bash
lex numberAnalyzer.l
```

---

### 3️⃣ Compile the C Code
Compile the generated C code with GCC and the Flex library:
```bash
gcc lex.yy.c -o numberAnalyzer -lfl
```

---

### 4️⃣ Run the Lexical Analyzer
Execute the program with an input file containing numbers:
```bash
./numberAnalyzer input.txt
```
Replace `input.txt` with the path to your input file.

---

## 📂 Example

### Input File (`input.txt`):
```
12
-45
0.67
-0.89
+100
-200.25
```

### Expected Output:
```
Number of +ve integers = 2
Number of -ve integers = 1
Number of +ve fractions = 1
Number of -ve fractions = 2
```

---

## 🛠 Code Explanation

1. **Lex Rules:**
   - `[-][0-9]+(\.[0-9]+)?`: Matches negative integers and fractions.
   - `[+]?[0-9]+(\.[0-9]+)?`: Matches positive integers and fractions.
   - `[ \t\n]+`: Ignores whitespace, tabs, and newlines.
   - `. `: Matches any other character and ignores it.

2. **Counters:**
   - `posint`: Counts positive integers.
   - `negint`: Counts negative integers.
   - `posfraction`: Counts positive fractions.
   - `negfraction`: Counts negative fractions.

3. **Main Function:**
   - Opens the input file and processes it using `yylex`.
   - Prints the count of each type of number after processing.

---

## 🛡️ Prerequisites

1. **Flex**: Install Flex using your system's package manager.
   ```bash
   sudo apt install flex         # For Debian-based systems
   sudo yum install flex         # For Red Hat-based systems
   brew install flex             # For macOS
   ```
2. **GCC**: Ensure GCC is installed for compiling the C code.

---

## 📜 License
This project is open source and free to use. Feel free to modify and share it as needed!

---

Enjoy coding! ✨
