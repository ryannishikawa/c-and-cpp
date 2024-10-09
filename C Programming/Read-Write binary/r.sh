#/bin/bash

#Program name "to-bin" "read-bin"
#Author: R. Nishikawa
#This file is the script file that accompanies the "to-bin" and "read-bin" programs.
#Prepare for execution in normal mode (not gdb mode).

#Delete some un-needed files
rm *.o
rm *.out

echo "Do a compiler check on student.h"
gcc to-bin.c -o compiler_check

echo "Compile the source file to-bin.c"
gcc  -m64 -Wall -no-pie -o to-bin.o -std=c2x -c to-bin.c

echo "Link the object modules to create an executable file"
gcc -m64 -no-pie -o to-bin.out to-bin.o -std=c2x -Wall -z noexecstack

echo "Compile the source file read-bin.c"
gcc  -m64 -Wall -no-pie -o read-bin.o -std=c2x -c read-bin.c

echo "Link the object modules to create an executable file"
gcc -m64 -no-pie -o read-bin.out read-bin.o -std=c2x -Wall -z noexecstack

#give the program permission to execute
chmod +x to-bin.out

#give the program permission to execute
chmod +x read-bin.out

echo "Run the program to-bin"
./to-bin.out

echo "Run the program read-bin"
./read-bin.out

echo "This bash script will now terminate."
