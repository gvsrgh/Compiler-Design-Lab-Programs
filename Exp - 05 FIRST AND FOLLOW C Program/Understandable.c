#include <stdio.h>
#include <ctype.h>
#include <string.h>

void calculateFirstForSymbol(char, int, int);
void calculateFollowForNonTerminal(char c);
void findFirstForNonTerminal(char c, int, int);

int totalProductions = 8, firstSetCount = 0, followSetCount = 0;
char firstSets[10][100];
char followSets[10][100];
char productions[10][10];
char follow[10], first[10];
int currentProduction;
char currentChar;
int epsilon;

int main(int argc, char **argv) {
    int firstSetIndex = 0, followSetIndex = 0;
    int i, choice;
    char nonTerminal, terminal;
    int productionIndex;
    int processedNonTerminalsIndex = -1;
    char processedNonTerminals[totalProductions];

    // Initialize productions
    strcpy(productions[0], "E=TR");
    strcpy(productions[1], "R=+TR");
    strcpy(productions[2], "R=#");
    strcpy(productions[3], "T=FY");
    strcpy(productions[4], "Y=*FY");
    strcpy(productions[5], "Y=#");
    strcpy(productions[6], "F=(E)");
    strcpy(productions[7], "F=i");

    // Initialize firstSets and followSets
    for(currentProduction = 0; currentProduction < totalProductions; currentProduction++) {
        for(productionIndex = 0; productionIndex < 100; productionIndex++) {
            firstSets[currentProduction][productionIndex] = '!';
            followSets[currentProduction][productionIndex] = '!';
        }
    }

    // Calculate FIRST sets
    int firstSetPointer = 0, point2, tempIndex;
    for(currentProduction = 0; currentProduction < totalProductions; currentProduction++) {
        nonTerminal = productions[currentProduction][0];
        point2 = 0;
        tempIndex = 0;

        // Skip if FIRST set has already been calculated for the non-terminal
        for(productionIndex = 0; productionIndex <= processedNonTerminalsIndex; productionIndex++) {
            if(nonTerminal == processedNonTerminals[productionIndex]) {
                tempIndex = 1;
                break;
            }
        }

        if (tempIndex == 1)
            continue;

        findFirstForNonTerminal(nonTerminal, 0, 0);
        processedNonTerminalsIndex += 1;
        processedNonTerminals[processedNonTerminalsIndex] = nonTerminal;

        // Print FIRST set
        printf("\nFirst(%c) = { ", nonTerminal);
        firstSets[firstSetIndex][point2++] = nonTerminal;
        for(i = firstSetPointer; i < firstSetCount; i++) {
            int duplicateCheck = 0, found = 0;
            for(duplicateCheck = 0; duplicateCheck < point2; duplicateCheck++) {
                if (first[i] == firstSets[firstSetIndex][duplicateCheck]) {
                    found = 1;
                    break;
                }
            }
            if(found == 0) {
                printf("%c, ", first[i]);
                firstSets[firstSetIndex][point2++] = first[i];
            }
        }
        printf("}\n");
        firstSetPointer = firstSetCount;
        firstSetIndex++;
    }

    printf("\n-----------------------------------------------\n\n");

    // Calculate FOLLOW sets
    char processedFollowNonTerminals[totalProductions];
    processedNonTerminalsIndex = -1;
    firstSetIndex = 0;
    int followPoint = 0;
    for(epsilon = 0; epsilon < totalProductions; epsilon++) {
        currentChar = productions[epsilon][0];
        point2 = 0;
        tempIndex = 0;

        // Skip if FOLLOW set has already been calculated for the non-terminal
        for(productionIndex = 0; productionIndex <= processedNonTerminalsIndex; productionIndex++) {
            if(currentChar == processedFollowNonTerminals[productionIndex]) {
                tempIndex = 1;
                break;
            }
        }

        if (tempIndex == 1)
            continue;

        followPoint += 1;
        calculateFollowForNonTerminal(currentChar);
        processedNonTerminalsIndex += 1;
        processedFollowNonTerminals[processedNonTerminalsIndex] = currentChar;

        // Print FOLLOW set
        printf("Follow(%c) = { ", currentChar);
        followSets[firstSetIndex][point2++] = currentChar;
        for(i = followSetIndex; i < followSetCount; i++) {
            int duplicateCheck = 0, found = 0;
            for(duplicateCheck = 0; duplicateCheck < point2; duplicateCheck++) {
                if (follow[i] == followSets[firstSetIndex][duplicateCheck]) {
                    found = 1;
                    break;
                }
            }
            if(found == 0) {
                printf("%c, ", follow[i]);
                followSets[firstSetIndex][point2++] = follow[i];
            }
        }
        printf("}\n\n");
        followSetIndex = followSetCount;
        firstSetIndex++;
    }

    return 0;
}

void calculateFollowForNonTerminal(char nonTerminal) {
    int i, j;
    if(productions[0][0] == nonTerminal) {
        follow[followSetCount++] = '$';
    }

    for(i = 0; i < 10; i++) {
        for(j = 2; j < 10; j++) {
            if(productions[i][j] == nonTerminal) {
                if(productions[i][j+1] != '\0') {
                    calculateFirstForSymbol(productions[i][j+1], i, j+2);
                }
                if(productions[i][j+1] == '\0' && nonTerminal != productions[i][0]) {
                    calculateFollowForNonTerminal(productions[i][0]);
                }
            }
        }
    }
}

void findFirstForNonTerminal(char nonTerminal, int productionIndex, int charIndex) {
    int j;
    if (!(isupper(nonTerminal))) {
        first[firstSetCount++] = nonTerminal;
    }

    for(j = 0; j < totalProductions; j++) {
        if(productions[j][0] == nonTerminal) {
            if(productions[j][2] == '#') {
                if(productions[productionIndex][charIndex] == '\0') {
                    first[firstSetCount++] = '#';
                }
                else if(productions[productionIndex][charIndex] != '\0' && (productionIndex != 0 || charIndex != 0)) {
                    findFirstForNonTerminal(productions[productionIndex][charIndex], productionIndex, (charIndex+1));
                }
                else {
                    first[firstSetCount++] = '#';
                }
            }
            else if(!isupper(productions[j][2])) {
                first[firstSetCount++] = productions[j][2];
            }
            else {
                findFirstForNonTerminal(productions[j][2], j, 3);
            }
        }
    }
}

void calculateFirstForSymbol(char symbol, int productionIndex, int charIndex) {
    int k;
    if(!(isupper(symbol))) {
        follow[followSetCount++] = symbol;
    } else {
        int i = 0, j = 1;
        for(i = 0; i < totalProductions; i++) {
            if(firstSets[i][0] == symbol) {
                break;
            }
        }

        while(firstSets[i][j] != '!') {
            if(firstSets[i][j] != '#') {
                follow[followSetCount++] = firstSets[i][j];
            } else {
                if(productions[productionIndex][charIndex] == '\0') {
                    calculateFollowForNonTerminal(productions[productionIndex][0]);
                } else {
                    calculateFirstForSymbol(productions[productionIndex][charIndex], productionIndex, charIndex+1);
                }
            }
            j++;
        }
    }
}
