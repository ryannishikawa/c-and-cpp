//****************************************************************************************************************************
//Program name: "trigonometry".  This program will show the date and time when the program executes and when given 2 sides of*
// a triangle and the angle between them will find the area of the triangle and the length of the third side. Copyright (C)  *
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
//  Program name: trigonometry
//  Due date+time: February 6, 2024 @ 11:59pm
//  Date of last update: February 4, 2024
//  Programming language(s): C
//  Files in this program: trigonometry.c
//  
//  OS of the computer where the program was developed: Ubuntu 22.04.3 LTS
//  OS of the computer where the program was tested: Ubuntu 22.04.3 LTS
//  Status: There are 3 user inputs.  The program performs correctly.
//
//References for this program
//  https://drive.google.com/file/d/1QXyvS094uCNT-abDgeA2Zb0dsdReZCTB/view
//  https://drive.google.com/file/d/1ND6OorPCJrOG8flAalyvtWf80FVPJc42/view
//
//Purpose
//  Show the current time. Solve a SAS triangle.
//
//This file
//   File name: trigonometry.c
//   Language: C
//   Compile: -m64 -Wall -no-pie -o trigonometry.o -std=c2x -c trigonometry.c -lm
//   Link: gcc -m64 -no-pie -o trig.out trigonometry.o -std=c2x -Wall -z noexecstack -lm
//
//References for this file
//   https://drive.google.com/file/d/1QXyvS094uCNT-abDgeA2Zb0dsdReZCTB/view
//   https://www.mathsisfun.com/algebra/trig-solving-sas-triangles.html
//   https://www.cuemath.com/measurement/area-of-triangle-with-2-sides-and-included-angle-sas/
//
//=======1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2**
//
//
//
//
//===== Begin code area ================================================================================================

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>

char *monthName(unsigned int monthNum); //function to convert month number to month name

int main(int argc, char* argv[]) {
    const double pi = 3.14159;
    //introduction
    printf("Welcome to Euclidean Triangles\n");
    printf("This software was built by and maintained by Systems Programmer Ryan Nisikawa.\n");

    //getting the current time
    time_t current_linux_time;
    char *ampm;
    current_linux_time = time(NULL);
    struct tm * broken = localtime(&current_linux_time);
    unsigned long hour = broken->tm_hour;
    if(broken == NULL)
        printf("A call to function localtime failed.\n");
    else {
        //convert to regular time
        ampm = "am";
        if (hour > 12) {
            hour -= 12;
            ampm = "pm";
        }

        //print time in month day, year at hour:minute am/pm
        printf("Today is %s %02d, %04d at %lu:%02d%s.\n",
                                           monthName(broken->tm_mon+1),
                                           broken->tm_mday,
                                           broken->tm_year+1900,
                                           hour,
                                           broken->tm_min,
                                           ampm);
    }

    //begin of trig stuff and getting the values
    printf("This program will manage all of your triangles.\n");
    printf("Enter a float number for each quantity first side, second side, and angle in degrees between those two sides. Separate each quantity by ws. After the third quantity press enter.\n");
    double side1, side2, side3, angle, area = 0.0;
    scanf("%lf %lf %lf", &side1, &side2, &angle);
    if(side1 < 0 || side2 < 0 || angle < 0) { //check for invalid(negative) input
        printf ("There are invalid Invalid data are among the inputs. Please run this program again\n");
    } else {
        printf("You entered %1.5lf and %1.5lf for sides and %1.5lf for the angle.\n", side1, side2, angle);
        
        //Math to solve a SAS triangle
        area = (0.5 * side1 * side2 * sin(angle * pi / 180.0));
        printf("The area of this triangle is %1.5lf square units.\n", area);
        side3 = (sqrt(pow(side1, 2.0) + pow(side2, 2.0) - (2.0 * side1 * side2 * cos(angle * pi / 180.0))));
        printf("The length of the third side of the triangle is %1.5lf linear units.\n", side3);
    }
    

    //time after Epoch
    printf("The time is now %lu s AE.\n", current_linux_time);
    

    //farewell
    printf("Have a nice day.\n");
    printf("An integer 0 will be sent to the operating system as a signal of successful execution. Bye.\n");
    return 0;

}

//function to convert month number to month name
char *monthName(unsigned int monthNum) {
    char *name;
    switch(monthNum) {
        case 1: name = malloc(8*sizeof(char));
                strcpy(name, "January");
                break;
        case 2: name = malloc(9*sizeof(char));
                strcpy(name, "February");
                break;
        case 3: name = malloc(6*sizeof(char));
                strcpy(name, "March");
                break;
        case 4: name = malloc(6*sizeof(char));
                strcpy(name, "April");
                break;
        case 5: name = malloc(4*sizeof(char));
                strcpy(name, "May");
                break;
        case 6: name = malloc(5*sizeof(char));
                strcpy(name, "June");
                break;
        case 7: name = malloc(5*sizeof(char));
                strcpy(name, "July");
                break;
        case 8: name = malloc(7*sizeof(char));
                strcpy(name, "August");
                break;
        case 9: name = malloc(10*sizeof(char));
                strcpy(name, "September");
                break;
        case 10: name = malloc(8*sizeof(char));
                 strcpy(name, "October");
                 break;
        case 11: name = malloc(9*sizeof(char));
                 strcpy(name, "November");
                 break;
        case 12: name = malloc(9*sizeof(char));
                 strcpy(name, "December");
                 break;
        default: name = malloc(14*sizeof(char));
                 strcpy(name, "Unknown Month");
                 break;
    }
    return name;
}