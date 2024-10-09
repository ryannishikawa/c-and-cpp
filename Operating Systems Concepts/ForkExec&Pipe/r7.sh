#/bin/bash

#Program name "7pipe.c"
#Author: R. Nishikawa
#This file is the script file that accompanies the "7pipe.c" program.
#Prepare for execution in normal mode (not gdb mode).

#Delete some un-needed files
rm *.o
rm *.out

echo "Compile the source file 7pipe.c"
gcc  -m64 -Wall -no-pie -o 7pipe.o -std=c2x -c 7pipe.c

echo "Link the object modules to create an executable file"
gcc -m64 -no-pie -o 7pipe.out 7pipe.o -std=c2x -Wall -z noexecstack

#give the program permission to execute
chmod +x 7pipe.out

echo "Run the program 7pipe.c"
./7pipe.out

echo "This bash script will now terminate."
