#/bin/bash

#Program name "4wait.c"
#Author: R. Nishikawa
#This file is the script file that accompanies the "4wait.c" program.
#Prepare for execution in normal mode (not gdb mode).

#Delete some un-needed files
rm *.o
rm *.out

echo "Compile the source file 4wait.c"
gcc  -m64 -Wall -no-pie -o 4wait.o -std=c2x -c 4wait.c

echo "Link the object modules to create an executable file"
gcc -m64 -no-pie -o 4wait.out 4wait.o -std=c2x -Wall -z noexecstack

#give the program permission to execute
chmod +x 4wait.out

echo "Run the program 4wait.c"
./4wait.out

echo "This bash script will now terminate."
