#/bin/bash

#Program name "Tokenizer"
#Author: R. Nishikawa
#This file is the script file that accompanies the "tokenizer" program.
#Prepare for execution in normal mode (not gdb mode).

#Delete some un-needed files
rm *.o
rm *.out

echo "Compile the source file tokenizer.c"
gcc  -m64 -Wall -no-pie -o tokenizer.o -std=c2x -c tokenizer.c

echo "Link the object modules to create an executable file"
gcc -m64 -no-pie -o tokenizer.out tokenizer.o -std=c2x -Wall -z noexecstack

#give the program permission to execute
chmod +x tokenizer.out

echo "Run the program Tokenizer"
./tokenizer.out

echo "This bash script will now terminate."
