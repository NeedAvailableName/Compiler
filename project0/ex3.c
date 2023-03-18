#include<stdio.h>
#include "charcode.h"
#include "charcode.c"
int main() {
    extern CharCode charCodes[];
    int numLine = 0, numLetter = 0, numDigit = 0;
    FILE *f;
    printf("Enter name of file to read: ");
    char fileName[50];
    scanf("%s", fileName);
    f = fopen(fileName, "r");
    if(f == NULL) printf("Cannot open file!");
    char c;
    do {
        c = fgetc(f);
        if(charCodes[c] == CHAR_LETTER) numLetter++;
        else if(charCodes[c] == CHAR_DIGIT) numDigit++;
        else if(c == 10 || c == -1) numLine++;
    } while(c != EOF);
    printf("Number of line: %d \n", numLine);
    printf("Number of letter: %d \n", numLetter);
    printf("Number of digit: %d \n", numDigit);
    fclose(f);
    return 0;
}