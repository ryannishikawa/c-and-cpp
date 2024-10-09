//****************************************************************************************************************************
//Program name: "read-bin".  This program will read a bin file and write it in text. Copyright (C)  *
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
//  Program name: read-bin.c
//  Due date+time: April 16 midpoint between April 15 and 16.
//  Date of last update: April 15, 2024
//  Programming language(s): C
//  Files in this program: to-bin.c, student.h, student.txt, read-bin.c
//  
//  OS of the computer where the program was developed: Ubuntu 22.04.3 LTS
//  OS of the computer where the program was tested: Ubuntu 22.04.3 LTS
//  Status: There is 1 user input. If the filename input is <ctrl+d> 
//          the program goes crazy. Otherwise, the program performs correctly.
//          Tested with: A bin file containing student info created with to-bin.c
//
//References for this program
//   lectures
//
//Purpose
//  read a binary file
//
//This file
//   File name: read-bin.c
//   Language: C
//   Compile: gcc  -m64 -Wall -no-pie -o read-bin.o -std=c2x -c read-bin.c
//   Link: gcc -m64 -no-pie -o read-bin.out read-bin.o -std=c2x -Wall -z noexecstack
//
//References for this file
//   lectures
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
#include "student.h"

const char* class_level(enum ClassLevel level); //function to help print enum ClassLevel

int main(int argc, char* argv[]) {
    printf("\n===== Begin execution ==========\n\n");
//get and open bin file
    char filename[256];
    FILE *bin = NULL;
    while(bin == NULL) {
        printf("Please enter the name of your file(<ctrl + c> to quit): ");
        scanf("%255s", filename);
        bin = fopen(filename, "rb");
        if (bin == NULL) {
            printf("Sorry. File was not found. Try again.\n");
        }
    }

//write info
    struct student_info person;
     while (0 < fread(&person, sizeof(struct student_info), 1, bin)) {
        printf("\nname = %s\n", person.name);
        printf("CWID = %lu\n", person.CWID);
        printf("major = %s\n", person.major);
        printf("class level = %s\n", class_level(person.class_level));
        printf("zip = %s\n", person.zip);
        printf("phoneNum = %s\n", person.phoneNum);
        printf("gpa = %0.1f\n", person.gpa);
    }

//end
    fclose(bin);
    printf("\n===== End execution ==========\n");
    return 0;
}