#/bin/bash

#Program name "records2"
#Author: R. Nishikawa
#This file is the script file that accompanies the "records2" programs.
#Prepare for execution in normal mode (not gdb mode).

#Delete some un-needed files
rm *.o
rm *.out

echo "Do a compiler check on student.h"
gcc records2.c -o compiler_check

echo "Compile the source file records2.c"
gcc  -m64 -Wall -no-pie -o records2.o -std=c2x -c records2.c

echo "Link the object modules to create an executable file"
gcc -m64 -no-pie -o records2.out records2.o -std=c2x -Wall -z noexecstack

#give the program permission to execute
chmod +x records2.out

echo "Run the program records2"
./records2.out

echo "This bash script will now terminate."
