#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char *str) {
    char k[32][10] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
        "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };
    int i;
    for (i = 0; i < 32; i++)
        if (strcmp(k[i], str) == 0)
            return 1;
    return 0;
}

int isFunction(char *str) {
    if (strcmp(str, "main") == 0 || strcmp(str, "printf") == 0)
        return 1;
    return 0;
}

int main() {
    int kc, lno = 1, sno = 0;
    char fn[20], c, buf[30];
    FILE *fp;

    printf("\nEnter the file name: ");
    scanf("%s", fn);

    printf("\n\nS.No         Token             Lexeme                  Line No");
    fp = fopen(fn, "r");
    
    if (fp == NULL) {
        printf("\nError opening file.");
        return 1;
    }

    while ((c = fgetc(fp)) != EOF) {
        if (isalpha(c)) {
            buf[kc = 0] = c;
            while (isalnum(c = fgetc(fp))) {
                buf[++kc] = c;
            }
            buf[++kc] = '\0';
            if (isKeyword(buf))
                printf("\n%4d        keyword          %20s      %7d", ++sno, buf, lno);
            else if (isFunction(buf))
                printf("\n%4d        function         %20s      %7d", ++sno, buf, lno);
            else
                printf("\n%4d       identifier        %20s      %7d", ++sno, buf, lno);
        } else if (isdigit(c)) {
            buf[kc = 0] = c;
            while (isdigit(c = fgetc(fp)))
                buf[++kc] = c;
            buf[++kc] = '\0';
            printf("\n%4d         number          %20s      %7d", ++sno, buf, lno);
        }

        if (c == '(' || c == ')')
            printf("\n%4d       parenthesis         %6c                  %7d", ++sno, c, lno);
        else if (c == '{' || c == '}')
            printf("\n%4d         brace             %6c                  %7d", ++sno, c, lno);
        else if (c == '[' || c == ']')
            printf("\n%4d       array index         %6c                  %7d", ++sno, c, lno);
        else if (c == ',' || c == ';')
            printf("\n%4d       punctuation         %6c                  %7d", ++sno, c, lno);
        else if (c == '"') {
            kc = -1;
            while ((c = fgetc(fp)) != '"' && c != EOF)
                buf[++kc] = c;
            buf[++kc] = '\0';
            printf("\n%4d         string           %20s      %7d", ++sno, buf, lno);
        } else if (c == ' ') {
            c = fgetc(fp);
        } else if (c == '\n') {
            ++lno;
        } else {
            printf("\n%4d         operator          %6c                  %7d", ++sno, c, lno);
        }
    }
    
    fclose(fp);
    return 0;
}
