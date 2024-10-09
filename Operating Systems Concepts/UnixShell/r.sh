#/bin/bash

#Program name "shell.c"
#Author: R. Nishikawa
#This file is the script file that accompanies the "shell.c" program.
#Prepare for execution in normal mode (not gdb mode).

#Delete some un-needed files
rm *.o
rm *.out

echo "Compile the source file shell.c"
gcc  -m64 -Wall -no-pie -o shell.o -std=c2x -c shell.c

echo "Link the object modules to create an executable file"
gcc -m64 -no-pie -o shell.out shell.o -std=c2x -Wall -z noexecstack

#give the program permission to execute
chmod +x shell.out

echo "Run the program shell.c"
./shell.out

echo "This bash script will now terminate."
