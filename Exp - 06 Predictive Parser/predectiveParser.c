#include <stdio.h>
#include <string.h>

char input[20];
int len, ln = 0, err = 0;

void E();
void E1();
void T();
void T1();
void F();
void match(char topChar);

void E() {
    T();
    E1();
}

void E1() {
    if (*input == '+') {
        match('+');
        T();
        E1();
    } else {
        return;
    }
}

void T() {
    F();
    T1();
}

void T1() {
    if (*input == '*') {
        match('*');
        F();
        T1();
    } else {
        return;
    }
}

void F() {
    if (*input == '(') {
        match('(');
        E();
        match(')');
    } else {
        match('i');
    }
}

void match(char topChar) {
    if (*input == topChar) {
        printf("\n%s popped %c", input, topChar);
        ln++;
        strcpy(input, &input[1]); // Pops matched input symbol from input
    } else {
        printf("\nError: '%c' was expected but not found.", topChar);
        err++;
    }
}

int main() {
    printf("Enter the Input: ");
    scanf("%s", input); // Using scanf instead of gets for safety

    len = strlen(input);
    input[len] = '$';  // Append `$` to mark the end of input
    input[len + 1] = '\0';

    E();

    if (err == 0 && ln == len) {
        printf("\n\nString parsed successfully!!!\n");
    } else {
        printf("\n\nString is not parsed successfully.\nErrors occurred or input contains invalid characters.\n\n");
    }

    return 0;
}
