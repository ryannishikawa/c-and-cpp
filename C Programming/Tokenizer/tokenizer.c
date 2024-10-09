//****************************************************************************************************************************
//Program name: "tokenizer".  This program will tokenize text from a .txt file and copy the tokens to a .tok file. Copyright (C)  *
//2024 Ryan Nishikawa                                                                                                        *
//This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License  *
//version 3 as published by the Free Software Foundation.                                                                    *
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied         *
//warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.     *
//A copy of the GNU General Public License v3 is available here:  <https://www.gnu.org/licenses/>.                           *
//****************************************************************************************************************************


//=======1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3**
//
//Author information
//  Author name: Ryan Nishikawa
//  Author email: ryannishikawa48@csu.fullerton.edu
//  Course ID: CPSC223C
//
//Program information
//  Program name: String Search
//  Due date+time: March 14, 2024 @ 2:00am
//  Date of last update: March 13, 2024
//  Programming language(s): C
//  Files in this program: tokenizer.c
//  
//  OS of the computer where the program was developed: Ubuntu 22.04.3 LTS
//  OS of the computer where the program was tested: Ubuntu 22.04.3 LTS
//  Status: There are 2 user inputs. If the filename input is <ctrl+d> 
//          the program goes crazy. Otherwise, the program performs correctly.
//          Tested with: A file containing no blanks and blank is the one separator, 
//                       a file containing only one byte, which is a blank,
//                       a file containing no data,
//                       a file containing 16 Z’s, and sheep.txt
//
//References for this program
//   stringSearch.c
//   https://www.geeksforgeeks.org/problem-with-using-fgets-gets-scanf-after-scanf-in-c/
//   https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/
//
//Purpose
//  Tokenize text from a text file
//
//This file
//   File name: tokenizer.c
//   Language: C
//   Compile: gcc  -m64 -Wall -no-pie -o tokenizer.o -std=c2x -c tokenizer.c
//   Link: gcc -m64 -no-pie -o tokenizer.out tokenizer.o -std=c2x -Wall -z noexecstack
//
//References for this file
//   stringSearch.c
//   https://www.geeksforgeeks.org/problem-with-using-fgets-gets-scanf-after-scanf-in-c/
//   https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/
//
//=======1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2**
//
//
//
//
//===== Begin code area ================================================================================================
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    //introduction
    printf("\n===== Begin execution ==========\n\n");
    printf("Welcome to Tokenizer brought to you by Ryan Nishikawa.\n\n");

    //get file + check if it opens successfully
    char filename[256];
    FILE *fp = NULL;
    while(fp == NULL) {
        printf("Please enter the name of your file(<ctrl + c> to quit): ");
        scanf("%255s", filename);
        fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("Sorry. File was not found. Try again.\n");
        }
    }
    //file opened with read permission successfully
    printf("\nThe file has been opened with read permission.\n");

    //get the file size in num char
    fseek(fp, 0, SEEK_END);
    unsigned long fileLen = ftell(fp);
    printf("The file contains %lu chars.\n", fileLen);

    //copy file to a 1D array
    rewind(fp);
    char text[fileLen];
    char d;
    unsigned long index = 0;
    while(EOF != (d = fgetc(fp))) {
        //if replaces  newlines with space
        if(d == '\n') {
            text[index] = ' ';
        } else {
            text[index] = d;
        }
        index++;
    }
    text[fileLen] = '\0';
    fclose(fp);
    printf("The file has been copied to a one-dimensional array and all newlines have been replaced by the space character.\n\n");

    //get the first 32 bytes
    printf("The first 32 bytes of the one-dimensional array are:\n");
    if(fileLen < 32) {
        for (unsigned char i = 0; i < fileLen; ++i) {
            printf("%c", text[i]);
        }
    } else {
        for (unsigned char i = 0; i < 32; ++i) {
            printf("%c", text[i]);
        }
    }


    //clear input buffer
    while ((getchar()) != '\n');
    //get the separator string
    printf("\n\nEnter some characters for the separator string and press <enter>: ");
    char separator[256];
    //use fgets bc it can read ws for the separator
    if(fgets(separator, 256, stdin) == NULL) {
        printf("**no token was found.\n");
        printf("\n===== End execution ==========\n");
        return 0;
    }

    //find the tokens and copy them into a 2d array
    char *DDarray[256] = {NULL};
    char *token;
    unsigned long j = 0;
    token = strtok(text, separator);
    do {
        //check if there's actaully a token before adding to the array
        if(token != NULL){
            DDarray[j] = token;
            j++;
        }
    } while(NULL != (token = strtok(NULL, separator)));

    //print the tokens and copy them into the .tok file
    printf("The tokens were found and placed into a two-dimensional array of char. Here are the contents of the token array in forward order.\n\n");
    unsigned long tokLen = 0;
        //create name for .tok file
    char *dot;
    dot = strrchr(filename, '.');
    strcpy(dot, ".tok");
        //create new file and open with write permission
    FILE *tokFP;
    tokFP = fopen(filename, "w");
    for(unsigned long a = 0; a < j; a++) {
        //print to terminal
        printf("%s\n", DDarray[a]);
        //copy to .tok file
        fprintf(tokFP, "%s\n", DDarray[a]);
        tokLen += strlen(DDarray[a]) + 1;
    }
    fclose(tokFP);

    //get the num of tokens and print
    printf("\nNumber of tokens is %lu\n\n", j);
    //more print stuff
    printf("The array of tokens has been written to a file named %s. It is generally called the token file.\n\n", filename);
    printf("You may view the token file by entering the command \"cat %s\".\n\n", filename);

    //print file size of .tok file
    printf("The file size of %s is %lu bytes\n\n", filename, tokLen);

    //the end
    printf("===== End execution ==========\n");
    return 0;
}
