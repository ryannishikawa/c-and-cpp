#/bin/bash

#Program name "calling fork"
#Author: R. Nishikawa
#This file is the script file that accompanies the "1_calling_fork.c" program.
#Prepare for execution in normal mode (not gdb mode).

#Delete some un-needed files
rm *.o
rm *.out

echo "Compile the source file 1_calling_fork.c"
gcc  -m64 -Wall -no-pie -o 1_calling_fork.o -std=c2x -c 1_calling_fork.c

echo "Link the object modules to create an executable file"
gcc -m64 -no-pie -o 1_calling_fork.out 1_calling_fork.o -std=c2x -Wall -z noexecstack

#give the program permission to execute
chmod +x 1_calling_fork.out

echo "Run the program 1_calling_fork.c"
./1_calling_fork.out

echo "This bash script will now terminate."
