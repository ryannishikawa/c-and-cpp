#/bin/bash

#Program name "read-bin"
#Author: R. Nishikawa
#This file is the script file that accompanies the "read-bin" program.
#Prepare for execution in normal mode (not gdb mode).

#Delete some un-needed files
rm *.o
rm *.out

echo "Do a compiler check on student.h"
gcc read-bin.c -o compiler_check

echo "Compile the source file read-bin.c"
gcc  -m64 -Wall -no-pie -o read-bin.o -std=c2x -c read-bin.c

echo "Link the object modules to create an executable file"
gcc -m64 -no-pie -o read-bin.out read-bin.o -std=c2x -Wall -z noexecstack

#give the program permission to execute
chmod +x read-bin.out

echo "Run the program read-bin"
./read-bin.out

echo "This bash script will now terminate."
