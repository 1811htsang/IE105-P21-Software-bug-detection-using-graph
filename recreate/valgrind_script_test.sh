#! /bin/bash

# Compiled sample test file for compiler
g++ -g compiler_testfile.cpp -o compiler_testfile -O0

# Add output file 
if [ ! -f "output.out" ]; then
    touch output.out
fi

# Echo for splitting the output of each tool
echo "memcheck information:" >> output.out

# Using valgrind memcheck tool
valgrind --tool=memcheck ./compiler_testfile &>> output.out 

# Echo for splitting the output of each tool
echo "" >> output.out
echo "thread information:" >> output.out

# Using valgrind threadcheck tool
valgrind --tool=helgrind ./compiler_testfile &>> output.out

# Echo for splitting the output of each tool
echo "" >> output.out
echo "data race information:\n" >> output.out

# Using valgrind dataracecheck tool
valgrind --tool=drd ./compiler_testfile &>> output.out