#/bin/bash

#Program name "3fork-exec.c"
#Author: R. Nishikawa
#This file is the script file that accompanies the "2fork.c" program.
#Prepare for execution in normal mode (not gdb mode).

#Delete some un-needed files
rm *.o
rm *.out

echo "Compile the source file 3fork-exec.c"
gcc  -m64 -Wall -no-pie -o 3fork-exec.o -std=c2x -c 3fork-exec.c

echo "Link the object modules to create an executable file"
gcc -m64 -no-pie -o 3fork-exec.out 3fork-exec.o -std=c2x -Wall -z noexecstack

#give the program permission to execute
chmod +x 3fork-exec.out

echo "Run the program 3fork-exec.c"
./3fork-exec.out

echo "This bash script will now terminate."
