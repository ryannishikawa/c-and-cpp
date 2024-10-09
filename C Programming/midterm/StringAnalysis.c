//Ryan Nishikawa
//ryannishikawa48@csu.fullerton.edu
//This course: “CPSC 223C”
//This product: “Midterm test”
//Today’s date: “March 14, 2024”

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    printf("\n===== Begin execution ==========\n\n");
    printf("Welcome to Sring Analysis brought to you by Ryan Nishikawa.\n\n");

//1
    char filename[256];
    FILE *fp = NULL;
    printf("Please enter the name of a file to analyze: ");
    while(fp == NULL) {
        scanf("%255s", filename);
        fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("File not found. Please try again: ");
        }
    }

//2
    fseek(fp, 0, SEEK_END);
    unsigned long fileLen = ftell(fp);
    rewind(fp);
    char text[fileLen];
    char d;
    unsigned long index = 0;
    while(EOF != (d = fgetc(fp))) {
        text[index] = d;
        index++;
    }
    text[fileLen] = '\0';

    char *DDarray[256] = {NULL};
    char *token;
    unsigned long j = 0;
    token = strtok(text, "\n");
    do {
        if(token != NULL){
            DDarray[j] = token;
            j++;
        }
    } while(NULL != (token = strtok(NULL, "\n")));
    printf("\nThe file has been copied to 2-dimensional array of row where each row is a string of chars\n");

//3
    unsigned long numChar = 0;
    for(unsigned long a = 0; a < j; a++) {
        numChar += strlen(DDarray[a]);
    }
    printf("There are %lu lines and %lu characters in this array.\n", j, numChar);

//4
    printf("\nHere is the data of that array.\n\n");
    for(unsigned long a = 0; a < j; a++) {
        printf("%s\n", DDarray[a]);
    }

//5
    char search[256];
    while ((getchar()) != '\n');
    printf("\nPease enter a string to search or press enter to quit: ");
    unsigned long loc[64];
    unsigned long locIndex = 0; // Reset locIndex to 0
    while (fgets(search, 256, stdin) != NULL && search[0] != '\n') { 
        search[strlen(search) - 1] = '\0';
        locIndex = 0; // Reset locIndex for each new search
        for (unsigned long i = 0; i < j; i++) {
            if(strstr(DDarray[i], search) != NULL){
                loc[locIndex] = i + 1;
                locIndex++;
            }
        }
        if (locIndex == 0) {
            printf("The string is not found");
        } else {
            printf("The string is in lines: ");
            for (unsigned long a = 0; a < locIndex; a++) {
                printf("%lu ", loc[a]);
            }
        }
        printf("\nPlease enter a string to search or press enter to quit: ");
    }



    printf("\nHave a good day. Bye.\n\n");
    printf("===== End execution ==========\n");
    return 0;
}