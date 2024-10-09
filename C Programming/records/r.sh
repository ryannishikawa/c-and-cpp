#/bin/bash

#Program name "records"
#Author: R. Nishikawa
#This file is the script file that accompanies the "to-bin" and "records" programs.
#Prepare for execution in normal mode (not gdb mode).

#Delete some un-needed files
rm *.o
rm *.out

echo "Do a compiler check on student.h"
gcc records.c -o compiler_check

echo "Compile the source file records.c"
gcc  -m64 -Wall -no-pie -o records.o -std=c2x -c records.c

echo "Link the object modules to create an executable file"
gcc -m64 -no-pie -o records.out records.o -std=c2x -Wall -z noexecstack

#give the program permission to execute
chmod +x records.out

echo "Run the program records"
./records.out

echo "This bash script will now terminate."
