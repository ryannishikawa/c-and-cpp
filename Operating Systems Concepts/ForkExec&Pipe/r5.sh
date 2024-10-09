#/bin/bash

#Program name "5waitpid.c"
#Author: R. Nishikawa
#This file is the script file that accompanies the "5waitpid.c" program.
#Prepare for execution in normal mode (not gdb mode).

#Delete some un-needed files
rm *.o
rm *.out

echo "Compile the source file 5waitpid.c"
gcc  -m64 -Wall -no-pie -o 5waitpid.o -std=c2x -c 5waitpid.c

echo "Link the object modules to create an executable file"
gcc -m64 -no-pie -o 5waitpid.out 5waitpid.o -std=c2x -Wall -z noexecstack

#give the program permission to execute
chmod +x 5waitpid.out

echo "Run the program 5waitpid.c"
./5waitpid.out

echo "This bash script will now terminate."
