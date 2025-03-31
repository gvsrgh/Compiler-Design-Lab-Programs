#include <stdio.h>
#include <string.h>

void calcFIRST(char[][25]);
void calcFOLLOW(char[][25]);
void getNonTs(char[][25]);
void printFIRST();

int n;
char *Ts = "abcdefghijklmnopqrstuvwxyz*.$3()+=-#";
char NonTs[26];
char first[26][20] ;
char follow[26][20] ;

int main(){
    printf("Calculating the FIRST and FOLLOW\n");
    printf("Enter the number of Productions: ");
    scanf("%d",&n);

    char prod[n][25];
    for(int i = 0; i < n; i++){
        printf("Enter the Production %d (without Spaces):", i);
        scanf("%s",prod[i]);
    }
    getNonTs(prod);
    calcFIRST(prod);
    return 0;
}

void getNonTs(char prod[][25]){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < strlen(prod[i]); j++){
            if('A' <= prod[i][j] && prod[i][j] <= 'Z')
                NonTs[prod[i][j] - 'A'] = 1;
        }
    }
}

void addTo(char array[], char element) {
    if (!strchr(array, element)) {
        int len = strlen(array);
        array[len] = element;
        array[len + 1] = '\0';
    }
}

void calcFIRST(char prod[][25]) {
    for (int i = 0; i < 26; i++) {
        if (NonTs[i] == 1) {
            char workingChars[20] = "";
            addTo(workingChars, 'A' + i);

            for (int a = 0; a < n; a++) {
                if (strchr(workingChars, prod[a][0])) {
                    if (prod[a][3] == '#') {
                        addTo(first[i], '#');
                    } else if (strchr(Ts, prod[a][3])) {
                        addTo(first[i], prod[a][3]);
                    } else if ('A' <= prod[a][3] && prod[a][3] <= 'Z') {
                        addTo(workingChars, prod[a][3]);
                    }
                }
            }
        }
    }
    printFIRST();
}

void printFIRST() {
    printf("\nFIRST Sets:\n");
    for (int i = 0; i < 26; i++) {
        if (NonTs[i] == 1) {
            printf("FIRST(%c): { ", 'A' + i);
            for (int j = 0; first[i][j] != '\0'; j++) {
                printf("%c ,", first[i][j]);
            }
            printf("}\n");
        }
    }
}

void calcFOLLOW(char prod[][25]){

}
