#/bin/bash

#Program name "trigonometry"
#Author: R. Nishikawa
#This file is the script file that accompanies the "trigonometry" program.
#Prepare for execution in normal mode (not gdb mode).

#Delete some un-needed files
rm *.o
rm *.out

echo "Compile the source file trigonometry.c"
gcc  -m64 -Wall -no-pie -o trigonometry.o -std=c2x -c trigonometry.c -lm

echo "Link the object modules to create an executable file"
gcc -m64 -no-pie -o trig.out trigonometry.o -std=c2x -Wall -z noexecstack -lm

#give the program permission to execute
chmod +x trig.out
./trig.out

echo "This bash script will now terminate."