#/bin/bash

#Program name "6stdout.c"
#Author: R. Nishikawa
#This file is the script file that accompanies the "6stdout.c" program.
#Prepare for execution in normal mode (not gdb mode).

#Delete some un-needed files
rm *.o
rm *.out

echo "Compile the source file 6stdout.c"
gcc  -m64 -Wall -no-pie -o 6stdout.o -std=c2x -c 6stdout.c

echo "Link the object modules to create an executable file"
gcc -m64 -no-pie -o 6stdout.out 6stdout.o -std=c2x -Wall -z noexecstack

#give the program permission to execute
chmod +x 6stdout.out

echo "Run the program 6stdout.c"
./6stdout.out

echo "This bash script will now terminate."
