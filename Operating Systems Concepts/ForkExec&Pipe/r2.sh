#/bin/bash

#Program name "2fork"
#Author: R. Nishikawa
#This file is the script file that accompanies the "2fork.c" program.
#Prepare for execution in normal mode (not gdb mode).

#Delete some un-needed files
rm *.o
rm *.out

echo "Compile the source file 2fork.c"
gcc  -m64 -Wall -no-pie -o 2fork.o -std=c2x -c 2fork.c

echo "Link the object modules to create an executable file"
gcc -m64 -no-pie -o 2fork.out 2fork.o -std=c2x -Wall -z noexecstack

#give the program permission to execute
chmod +x 2fork.out

echo "Run the program 2fork.c"
./2fork.out

echo "This bash script will now terminate."
