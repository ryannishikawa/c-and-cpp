//****************************************************************************************************************************
//Program name: "String Search".  This program will search through a text file for instances of a given string. Copyright (C)  *
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
//  Due date+time: February 21, 2024 @ 11:59pm
//  Date of last update: February 19, 2024
//  Programming language(s): C
//  Files in this program: stringSearch.c
//  
//  OS of the computer where the program was developed: Ubuntu 22.04.3 LTS
//  OS of the computer where the program was tested: Ubuntu 22.04.3 LTS
//  Status: There are at least 2 user inputs. If the filename input is <ctrl+d> 
//          the program goes crazy. Otherwise, the program performs correctly.
//          Tested with: https://courses.cs.washington.edu/courses/cse163/20wi/files/lectures/L04/bee-movie.txt and sheep.txt
//
//References for this program
//   https://drive.google.com/file/d/1xDgtIhgwcmEiwpqjnmb1kwtRwx6c4hcq/view
//   https://drive.google.com/file/d/1OxD4lwCluwU2uZl3TPoyJQYLDmWj1wE9/view
//   https://drive.google.com/file/d/1LCuul5KEOP20HtR8nasDZ70Xt7N3bBxx/view
//   https://www.ibm.com/docs/en/i/7.4?topic=functions-scanf-read-data#scanf__title__7
//
//
//Purpose
//  To search for a given string from a text file
//
//This file
//   File name: stringSearch.c
//   Language: C
//   Compile: gcc  -m64 -Wall -no-pie -o stringSearch.o -std=c2x -c stringSearch.c
//   Link: gcc -m64 -no-pie -o sSearch.out stringSearch.o -std=c2x -Wall -z noexecstack
//
//References for this file
//   https://drive.google.com/file/d/1xDgtIhgwcmEiwpqjnmb1kwtRwx6c4hcq/view
//   https://drive.google.com/file/d/1OxD4lwCluwU2uZl3TPoyJQYLDmWj1wE9/view
//   https://drive.google.com/file/d/1LCuul5KEOP20HtR8nasDZ70Xt7N3bBxx/view
//   https://www.ibm.com/docs/en/i/7.4?topic=functions-scanf-read-data#scanf__title__7
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
    printf("Welcome to Great String Search brought to you by Ryan Nishikawa.\n\n");

    //get file + check if it opens successfully
    char filename[256];
    FILE *fp = NULL;
    while(fp == NULL) {
        printf("Please enter the name of your file: ");
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
    printf("The file contains %ld chars.\n", fileLen);

    //copy file to a 1D array
    rewind(fp);
    char text[fileLen];
    char d;
    unsigned long index = 0;
    while(EOF != (d = fgetc(fp))) {
        text[index] = d;
        index++;
    }
    printf("The file has been copied to a one-dimensional array.\n\n");

    //get and find search string
    char target[256];
    printf("Enter a string to find or enter <ctrl+d> to terminate: ");
    while(EOF != (scanf("%255s", target))) {
        index = 0;
        unsigned long loc[fileLen / strlen(target)];
        unsigned long here = 0; //index to loc

        while (index < (fileLen - strlen(target))) {
            if (strncmp(text + index, target, strlen(target)) == 0) {
                loc[here] = index;
                here++;
            }
            index++;
        }//end inner while loop

        //print positions of target/contents of loc
        printf("%s was found %lu times at positions: ", target, here);
        if (here == 0) {
            printf("none");
        } else {
            for(int i = 0; i < here; i++) {
            printf("%lu", loc[i]);
            if (i < (here - 1))
            printf(", ");
        }
        }
        printf("\n\nEnter a string to find or enter <ctrl+d> to terminate: ");
    }

    //close file and exit
    fclose(fp);
    printf("<ctrl+d>\nThank you for using this search program.\n\n");
    printf("Have a good day. We hope you enjoyed the string search.\n");
    printf("Come back any time for more searching. Bye.\n\n");
    printf("===== End execution ==========\n");
    return 0;
}