#include<stdio.h>
#include<ctype.h>
int main() {
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
        if(isalpha(c)) numLetter++;
        else if(isdigit(c)) numDigit++;
        else if(c == '\n' || c == EOF) numLine++;
    }
    while(c != EOF);
    printf("Number of line: %d \n", numLine);
    printf("Number of letter: %d \n", numLetter);
    printf("Number of digit: %d \n", numDigit);
    fclose(f);
    return 0;
}