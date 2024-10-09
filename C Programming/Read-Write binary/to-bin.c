//****************************************************************************************************************************
//Program name: "to-bin".  This program will convert a .txt file to a .bin file. Copyright (C)  *
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
//  Program name: to-bin
//  Due date+time: April 16 midpoint between April 15 and 16.
//  Date of last update: April 15, 2024
//  Programming language(s): C
//  Files in this program: to-bin.c, student.h, student.txt, read-bin.c
//  
//  OS of the computer where the program was developed: Ubuntu 22.04.3 LTS
//  OS of the computer where the program was tested: Ubuntu 22.04.3 LTS
//  Status: There is 1 user input. If the filename input is <ctrl+d> 
//          the program goes crazy. Otherwise, the program performs correctly.
//          Tested with: A file containing student info seperated by newlines
//
//References for this program
//   lectures
//
//Purpose
//  convert a text file to a binary file
//
//This file
//   File name: to-bin.c
//   Language: C
//   Compile: gcc  -m64 -Wall -no-pie -o to-bin.o -std=c2x -c to-bin.c
//   Link: gcc -m64 -no-pie -o to-bin.out to-bin.o -std=c2x -Wall -z noexecstack
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

enum ClassLevel getClassLevel(const char *str); //function to help read enum ClassLevel from file

int main(int argc, char* argv[]) {
//introduction
    printf("\n===== Begin execution ==========\n\n");
    printf("Welcome to Welcome to Manage Academic Data brought to you by Ryan Nishikawa.\n\n");

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
    printf("\nYou entered %s\n", filename);
//create name for .bin file
    char *dot;
    dot = strrchr(filename, '.');
    strcpy(dot, ".bin");
    printf("The output file name is %s\n", filename);

//open bin file
    FILE *bin = NULL;
    bin = fopen(filename, "wb");

//read from file
    struct student_info person;
    while(fgets(person.name, 40, fp) != NULL) {
    //get name
        person.name[strlen(person.name) - 1] = '\0'; //remove newline
    //get cwid
        fscanf(fp, "%lu", &person.CWID);
        getc(fp);
    //get major
        fgets(person.major, 40, fp);
        person.major[strlen(person.major) - 1] = '\0'; //remove newline
    //get class level
        char class[22];
        fgets(class, sizeof(class), fp);
        class[strlen(class) - 1] = '\0';
        person.class_level = getClassLevel(class);
    //get zip code
        fgets(person.zip, sizeof(person.zip), fp);
        person.zip[strlen(person.zip) - 1] = '\0';
    //get phone num
        fgets(person.phoneNum, sizeof(person.phoneNum), fp);
        person.phoneNum[strlen(person.phoneNum) - 1] = '\0'; //remove newline
    //get gpa
        fscanf(fp, "%g", &person.gpa);
        getc(fp);
//write to bin file and terminal
        printf("\nname = %s\n", person.name);
        printf("CWID = %lu\n", person.CWID);
        printf("major = %s\n", person.major);
        printf("class level = %s\n", class);
        printf("zip = %s\n", person.zip);
        printf("phoneNum = %s\n", person.phoneNum);
        printf("gpa = %0.1f\n", person.gpa); 
        fwrite(&person, sizeof(struct student_info), 1, bin);
    }
    printf("\nThe binary file was created.\n");

//the end
    fclose(fp);
    fclose(bin);
    printf("\n===== End execution ==========\n");
    return 0;
}

enum ClassLevel getClassLevel(const char *str) {
    if (strcmp(str, "Freshman") == 0) {
        return Freshman;
    } else if (strcmp(str, "Sophomore") == 0) {
        return Sophomore;
    } else if (strcmp(str, "Junior") == 0) {
        return Junior;
    } else if (strcmp(str, "Senior") == 0) {
        return Senior;
    } else {
        return 5;
    }
}