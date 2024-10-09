#/bin/bash

#Program name "String Search"
#Author: R. Nishikawa
#This file is the script file that accompanies the "trigonometry" program.
#Prepare for execution in normal mode (not gdb mode).

#Delete some un-needed files
rm *.o
rm *.out

echo "Compile the source file stringSearch.c"
gcc  -m64 -Wall -no-pie -o stringSearch.o -std=c2x -c stringSearch.c

echo "Link the object modules to create an executable file"
gcc -m64 -no-pie -o search.out stringSearch.o -std=c2x -Wall -z noexecstack

#give the program permission to execute
chmod +x search.out

echo "Run the program String Search"
./search.out

echo "This bash script will now terminate."