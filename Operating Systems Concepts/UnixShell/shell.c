//****************************************************************************************************************************
//Program name: "shell.c".  This program will C design a shell in Linux. Copyright (C)  *
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
//  Course ID: CPSC351
//
//Program information
//  Program name: shell.c
//  Due date+time: October 5, 2024
//  Date of last update: October 4, 2024
//  Programming language(s): C
//  Files in this program: shell.c, r.sh
//  
//  OS of the computer where the program was developed: Ubuntu 22.04.3 LTS
//  OS of the computer where the program was tested: Ubuntu 22.04.3 LTS
//  Status: most commands work, but if its something specifically weird (i.e 3 spaces before final ECHO) output is wonky
//
//References for this program
//  https://www.geeksforgeeks.org/making-linux-shell-c/#
//  https://www.geeksforgeeks.org/c-program-display-hostname-ip-address/
//  https://www.quora.com/How-do-you-color-the-output-of-a-program-in-C
//  https://www.geeksforgeeks.org/zombie-processes-prevention/
//  
//
//Purpose
//  to design a shell in linux
//
//This file
//   File name: shell.c
//   Language: C
//   Compile: gcc  -m64 -Wall -no-pie -o shell.o -std=c2x -c shell.c
//   Link: gcc -m64 -no-pie -o shell.out shell.o -std=c2x -Wall -z noexecstack
//
//=======1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2**
//
//
//
//
//===== Begin code area ================================================================================================
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //for gethostname(), idk why it gives error 
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>

#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported

// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

//helper functions
//function to get and print name of computer
void printhostname();
//function to echo
void echo(char cmd_line[]);
//function to exec cmd
void exeggutor(char *args[], size_t arrLen);
void exeggcute(short *in_out, char *filename, char *argArr[], size_t i);
//functions for cmd line redirection 
    //out
void get_out(char filename[]);
    //in
void get_in(char filename[]);
//(7)
void lay_pipe(size_t where, char *argArr[], char *filename, size_t i);
//parse
void parse_args(char args[], short *in_out, size_t *i, size_t *j, char *filename, size_t n, char *argArr[], size_t *pipe_exist);


int main() {
    //introduction
    printf("\n======================================== Begin execution ========================================\n\n");
    printf("\n                             Welcome to a Unix Shell by Ryan Nishikawa.\n\n");
    printf("\n======================================== Begin execution ========================================\n\n");

//read cmd line input
    char args[MAXCOM];
    char prev_args[MAXCOM];
    printhostname();
    while (fgets(args, sizeof(args), stdin)) {
        char *argArr[MAXLIST];
        size_t i = 0;
        size_t j = 0;
        char *filename;
        char buffer[256];
        short in_out = 0;
        char repeat[2];
        size_t pipe_exist = 0;
        sscanf(&args[0], "%s", repeat);
        if (strcmp(repeat, "!!") == 0) { strcpy(args, prev_args); }
        parse_args(args, &in_out, &i, &j, filename = buffer, sizeof(buffer), (char **)argArr, &pipe_exist);
        if (strcmp(argArr[i - 1], "ECHO") == 0) {
            argArr[i - 1] = " ";
            i--;
            echo(args);
        }
//execute command
        if (i < (MAXLIST - 1) && i > 0) {
            argArr[i] = NULL;
            //dec i so i = arglist last arg
            i--;
    // (6)
            if (pipe_exist == 0) { exeggcute(&in_out, filename, argArr, i); } 
            else { lay_pipe(pipe_exist, argArr, filename, i); }
        } else {
            fprintf(stderr, "**Error too few/many commands, please try again.**\n");
        }
        strcpy(prev_args, args);
        printhostname();
    }
    
    

    return 0;
}




//function definitions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//(7) can fork/exec two programs with pipes between them
void lay_pipe(size_t where, char *argArr[], char *filename, size_t i) {
    int fpipe[2];
    if (pipe(fpipe) == -1) { 
        fprintf(stderr, "Pipe failed\n"); 
        exit(1);
    }
    int rc1 = fork();
    if (rc1 < 0) { fprintf(stderr, "Error: call to fork() failed.\n"); } 
    else if (rc1 == 0) {
        char *argArr1[MAXLIST];
        size_t i1 = 0;
        while (i1 < where) { 
            argArr1[i1] = argArr[i1]; 
            i1++;
        }
        argArr1[i1] = NULL;
        close(fpipe[0]);
        dup2(fpipe[1], STDOUT_FILENO);
        exeggutor(argArr1, i1);
        exit(0);
    } else {
        int letswait;
        waitpid(rc1, &letswait, 0);
        int rc2 = fork();
        if (rc2 < 0) { fprintf(stderr, "Error: call to fork() failed.\n"); } 
        else if (rc2 == 0) {
            char *argArr2[MAXLIST];
            size_t i2 = 0;
            while (i2 < (i - where)) { 
                argArr2[i2] = argArr[where + i2 + 1]; 
                i2++;
            }
            argArr2[i2] = NULL;
            close(fpipe[1]);
            dup2(fpipe[0], STDIN_FILENO);
            exeggutor(argArr2, i2);
            exit(1);
        } else {
            close(fpipe[0]);
            close(fpipe[1]);
            int letswait2;
            waitpid(rc2, &letswait2, 0);
        }
        
    }
}

void parse_args(char args[], short *in_out, size_t *i, size_t *j, char *filename, size_t n, char *argArr[], size_t *pipe_exist) {
    size_t i2 = 0;
    size_t j2 = 0;
    char filename2[256];
    short in_out2 = 0;
//each arg can be up to 100 chars
    char cmd[MAXLIST];
//read words from args and put in array
    while (sscanf(&args[j2], "%s", cmd) > 0) {
// (6) can fork/exec one command WITH command line redirection: 
    //output ">"
        if (cmd[0] == '>') {
            if (strcmp(cmd, ">") == 0) {
                j2 += 2;
                sscanf(&args[j2], "%s", filename2);
                j2 += (strlen(filename2) + 1);
            } else {
                strcpy(filename2, &cmd[1]);
                j2 += (strlen(cmd)-1);
            }
            in_out2 = 2;
            memset(cmd, 0, sizeof(cmd));
        }
    //input "<"
        if (cmd[0] == '<') {
            if (strcmp(cmd, "<") == 0) {
                j2 += 2;
                sscanf(&args[j2], "%s", filename2);
                j2 += (strlen(filename2) + 1);
            } else {
                strcpy(filename2, &cmd[1]);
                j2 += (strlen(cmd)-1);
            }
            in_out2 = 1;
            sscanf(&args[j2], "%s", cmd);
        }
    //find pipe
        if (strcmp(cmd, "|") == 0) {
            *pipe_exist = i2;
        }
        j2 += (strlen(cmd)+1);
        argArr[i2] = strdup(cmd);
        i2++;
    }
    *i = i2;
    *j = j2;
    strncpy(filename, filename2, n - 1);
    *in_out = in_out2;

}

void get_out(char filename[]) {
    int output = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output < 0) { printf("**Error could not open/create file, please try again.**\n"); }
    dup2(output, STDOUT_FILENO);
    close(output);
}

void get_in(char filename[]) {
    int input = open(filename, O_RDONLY);
    if (input < 0) { printf("**Error %s does not exist, please try again.**\n", filename); }
    dup2(input, STDIN_FILENO);
    close(input);
}   

void exeggcute(short *in_out, char *filename, char *argArr[], size_t i) {
    if (*in_out == 1) { 
        *in_out = 0; 
        int rc = fork();
        if (rc < 0) { fprintf(stderr, "Error: call to fork() failed.\n"); } 
        else if (rc == 0) {
            get_in(filename); 
            exeggutor(argArr, i);
            exit(1);
        } else { 
            int letswait;
            waitpid(rc, &letswait, 0);
        }
    } 
    else if (*in_out == 2) { 
        *in_out = 0;
        int rc = fork();
        if (rc < 0) { fprintf(stderr, "Error: call to fork() failed.\n"); } 
        else if (rc == 0) {
            get_out(filename); 
            exeggutor(argArr, i);
            exit(1);
        } else { 
            int letswait;
            waitpid(rc, &letswait, 0);
        }
    }
    else { exeggutor(argArr, i); }
}

void exeggutor(char *args[], size_t arrLen){
//run commands
//(4) can run built-in commands:  help, cd, mkdir, exit, !!
//help
    if (strcmp(args[0], "help") == 0) {
        printf("Available commands: help, cd, mkdir, exit, !!, all other general commands available in UNIX shell\n");
//cd
    } else if (strcmp(args[0], "cd") == 0) {
        if (arrLen > 2) { fprintf(stderr, "cd: too many arguments\n"); } 
        else {
            int move = 0;
            if (args[1] == NULL) { move = chdir(getenv("HOME")); } 
            else { 
                move = chdir(args[1]); 
                printf("cd: Moved to \033[1;32m/%s\033[0m\n", args[1]);
            }
            if (move < 0) {
                fprintf(stderr, "cd: \033[1;32m%s\033[0m: No such file or directory\n", args[1]);
            }
        }
//mkdir
    } else if (strcmp(args[0], "mkdir") == 0) {
        if (arrLen > 2) { fprintf(stderr, "mkdir: too many arguments\n"); } 
        else {
            int create = 0;
            if (args[1] == NULL) { fprintf(stderr, "mkdir: missing operand\n"); } 
            else { 
                create = mkdir(args[1], S_IRWXU | S_IRWXG | S_IRWXO); 
                printf("mkdir: \033[1;32m%s\033[0m created\n", args[1]);
            }
            if (create < 0) {
                fprintf(stderr, "mkdir: \033[1;32m%s\033[0m: Failed to create directory\n", args[1]);
            }
        }
//exit
    } else if (strcmp(args[0], "exit") == 0) {
        printf("\n======================================== End execution ========================================\n\n");
        printf("\n                                          Goodbye o7.\n\n");
        printf("\n======================================== End execution ========================================\n\n");
        exit(1);
//!! (implemented towards the beginning)
    } else if (strcmp(args[0], "!!") == 0) {
        printf("why are you here????\n");
//(5) can fork/exec one command without command line redirection
    } else {
        int rc = fork();
        if (rc < 0) {
            fprintf(stderr, "Error: call to fork() failed.\n"); 
        } else if (rc == 0) {
            int status = execvp(args[0], args);
            if (status == -1) {
                fprintf(stderr, "%s: command not found\n", args[0]);
                exit(1); 
            }
        } else {
            int letswait;
            waitpid(rc, &letswait, 0);
        }
    }

}

void echo(char cmd_line[]) {
//(1) parses commands and can echo them back as a series of words, one word per line, if the last word on the line is ECHO
//doesnt work if more than 2 spaces between ECHO and prev argument.
    printf("===================\n");
    printf("ECHO ECHO ECHO ECHO");
    printf("\n===================\n");
    bool prev_is_space = false; //in case there are multiple space back to back
    while(*cmd_line) {
    // (2) can print SPACE for each space char it finds in the input
        if (*cmd_line == ' ') {
            if(prev_is_space) {
                printf("SPACE\n");
            } else {
                printf("\nSPACE\n");
            }
            prev_is_space = true;
    // (3) can print PIPE for each pipe it finds in the input
    //doesn't account for back-to-back pipes
        } else if (*cmd_line == '|') {
            printf("PIPE");
            prev_is_space = false;
        } else {
            printf("%c", *cmd_line);
            prev_is_space = false;
        }
        *cmd_line++;
    }
    printf("===================\n");
    printf("     COMMAND");
    printf("\n===================\n");
}

void printhostname() {
//comp name
    char hostbuffer[256];
    gethostname(hostbuffer, sizeof(hostbuffer));
//print hostname in green
    printf("\033[1;33mryannishikawa-unix-shell-proj@%s\033[31m(\"exit\" to quit) \033[0m>> ", hostbuffer);
}