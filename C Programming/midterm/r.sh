#/bin/bash

#Program name "String Analysis"
#Author: R. Nishikawa
#This file is the script file that accompanies the "String Analysis" program.
#Prepare for execution in normal mode (not gdb mode).

#Delete some un-needed files
rm *.o
rm *.out

echo "Compile the source file StringAnalysis.c"
gcc  -m64 -Wall -no-pie -o StringAnalysis.o -std=c2x -c StringAnalysis.c

echo "Link the object modules to create an executable file"
gcc -m64 -no-pie -o str.out StringAnalysis.o -std=c2x -Wall -z noexecstack

#give the program permission to execute
chmod +x str.out

echo "Run the program StringAnalysis"
./str.out

echo "This bash script will now terminate."
